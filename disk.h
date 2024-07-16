void printCommandChannel(unsigned char file, unsigned char device, unsigned char channel);
unsigned char readDriveStatus(unsigned char file, unsigned char device, unsigned char channel);
void sendDriveCommand(unsigned char file, unsigned char device, unsigned char channel, char * command);
void loadCommand(unsigned char file, unsigned char device, unsigned char channel, char * fileName);