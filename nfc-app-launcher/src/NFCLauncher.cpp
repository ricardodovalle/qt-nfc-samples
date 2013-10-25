/*
 ============================================================================
 Name		: NFCLauncher.cpp
 Author	  : Lucian Tomuta
 Copyright   : 2011 Forum Nokia
 Description : Exe source file
 ============================================================================
 */

//  Include Files  

#include "NFCLauncher.h"
#include <e32base.h>
#include <e32std.h>

#include <apgcli.h> // for RApaLsSession
#include <apacmdln.h> // for CApaCommandLine
#include <aknglobalnote.h>
#include <featdiscovery.h>
#include <hal.h>
#include <barsc.h>
#include <bautils.h>
#include <f32file.h>

#include <NFCLauncher.rsg>

//  Constants
const TUid KAppToLaunchAppUid = {0xA00002D6};

const TInt KModelRm675 = 0x2002bf92;
#define KFeatureIdNfc 117

//  Local Functions

TBool ProductSupportsNfcViaFirmwareUpdate()
{
    TBool supportsNfcViaFirmwareUpdate = EFalse;
    TInt model = 0;

#if defined(__WINS__)
    supportsNfcViaFirmwareUpdate = ETrue;
#else
    const TInt error( HAL::Get(HALData::EModel, model) );
    if (( error == KErrNone ) && ( model == KModelRm675 ))
            supportsNfcViaFirmwareUpdate = ETrue;
#endif
    
    return supportsNfcViaFirmwareUpdate;
} 

void ShowNoteL(const TDesC& aMessage)
{
	CAknGlobalNote* note = CAknGlobalNote::NewL();
	TInt noteId = note->ShowNoteL(EAknGlobalInformationNote ,aMessage);
	User::After(3000000);
	note->CancelNoteL(noteId);
}

TBool HandleNfcFeatureSupportL(TBool aMandatory=ETrue)
{
	TBool result = EFalse;
	
	if ( CFeatureDiscovery::IsFeatureSupportedL(KFeatureIdNfc) )
		result = ETrue;
    else if ( ProductSupportsNfcViaFirmwareUpdate() )
	{
		TFileName path;
		
		#if defined(__WINS__)
		_LIT(KZSystemDataHelloRsc,"Z:\\resource\\apps\\NFCLauncher_E1234567.rsc");
		path.Copy(KZSystemDataHelloRsc);
		#else
		// get the path of the current process
		RProcess process;
		RApaLsSession apaLsSession;
		User::LeaveIfError(apaLsSession.Connect());
		CleanupClosePushL(apaLsSession);
		TApaAppInfo appInfo;
		User::LeaveIfError(apaLsSession.GetAppInfo(appInfo, process.SecureId()));
		CleanupStack::PopAndDestroy(&apaLsSession);    
		// construct path to resource file
		path.Copy(appInfo.iFullName.Left(2));
		path.Append(_L("\\resource\\apps\\NFCLauncher_E1234567.rsc"));				
		#endif

		RFs fsSession;
		User::LeaveIfError(fsSession.Connect());
		CleanupClosePushL(fsSession);

		// open resource file
		RResourceFile resourceFile; // resource file pointer
		BaflUtils::NearestLanguageFile(fsSession, path);
		resourceFile.OpenL(fsSession, path);
		CleanupClosePushL(resourceFile);
		
		HBufC8* dataBuffer = NULL;
		if(aMandatory)
		{
			dataBuffer=resourceFile.AllocReadLC(NFC_MANDATORY);
		}
		else
		{
			dataBuffer=resourceFile.AllocReadLC(NFC_RECOMMENDED);
			result = ETrue;
		}

		TResourceReader reader;
		reader.SetBuffer(dataBuffer);
		TPtrC textdata = reader.ReadTPtrC();

		// show the message
		ShowNoteL(textdata);

		// clean up data buffer
		CleanupStack::PopAndDestroy(3, &fsSession); // finished with dataBuffer, resourceFile, fsSession	
	}

    return result; 
} 

void LaunchAppL(const TUid aAppUid)
{
	RApaLsSession apaLsSession;
	User::LeaveIfError(apaLsSession.Connect());
	CleanupClosePushL(apaLsSession);
	TApaAppInfo appInfo;
	
	User::LeaveIfError(apaLsSession.GetAppInfo(appInfo, aAppUid));
	
	CApaCommandLine* cmdLine = CApaCommandLine::NewLC();
	cmdLine->SetExecutableNameL(appInfo.iFullName);
	cmdLine->SetCommandL(EApaCommandRun);
	
	User::LeaveIfError( apaLsSession.StartApp(*cmdLine) );
	
	CleanupStack::PopAndDestroy(cmdLine);        
	CleanupStack::PopAndDestroy(&apaLsSession);    
}


LOCAL_C void MainL()
	{
	//
	// add your program code here, example code below
	//
	
	TBool canContinue = EFalse;
	TRAPD(error, canContinue = HandleNfcFeatureSupportL());
	if(canContinue)
		{
		TRAPD(error, LaunchAppL(KAppToLaunchAppUid));
		}
	}

LOCAL_C void DoStartL()
	{
	// Create active scheduler (to run active objects)
//	CActiveScheduler* scheduler = new (ELeave) CActiveScheduler();
//	CleanupStack::PushL(scheduler);
//	CActiveScheduler::Install(scheduler);

	TRAPD(ignore, MainL());
	
	// Delete active scheduler
//	CleanupStack::PopAndDestroy(scheduler);
	}

//  Global Functions

GLDEF_C TInt E32Main()
	{
	// Create cleanup stack
	__UHEAP_MARK;
	CTrapCleanup* cleanup = CTrapCleanup::New();

	// Run application code inside TRAP harness
	TRAPD(mainError, DoStartL());
	
	delete cleanup;
	__UHEAP_MARKEND;
	return KErrNone;
	}

