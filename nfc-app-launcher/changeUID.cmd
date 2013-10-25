@echo off
echo Please use the command with a parameter. See readme.txt. > UID_changelog.txt

if "%1"=="" goto theend

echo Changing the UID3 to 0x%1 > UID_changelog.txt
fart -r .\*.rss "E1234567" "%1" >> UID_changelog.txt
fart -r .\*.mk "E1234567" "%1" >> UID_changelog.txt
fart -r .\*.mmp "E1234567" "%1" >> UID_changelog.txt
fart -r .\*.pkg "E1234567" "%1" >> UID_changelog.txt
fart -r .\*.cpp "E1234567" "%1" >> UID_changelog.txt
fart -r .\changeUID.cmd "E1234567" "%1"
echo Done. >> UID_changelog.txt

:theend

