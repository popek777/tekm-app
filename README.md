
# tekm-app

to install third parties run:
./init_thirdparties.sh

to build run: 
./build.sh

to execute run:
./Build/tekm-app


NOTES:

since boost property tree, nor tooska xml parsing libraries didn't cope with
parsing time.com html content, I decided to go with poor (since it will not work 
when html content of time.com will change it's format) manual solution of
parsing html content string 

