#pragma once

//LoginServer commands
#define CORRECT 0x0000
#define AUTHSUCCESS 0x0001
#define RIGHTCREDENTIALS 0x0002
#define AUTHFAIL 0x0003
#define WRONGCREDENTIALS 0x0004
#define USERALREADYEXISTS 0x0005

//Server commands
#define SENDMESSAGE 0x0001
