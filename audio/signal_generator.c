#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>

#include <unistd.h>

#define BATCH_SIZE 512

int main(int argc, char *argv[])
{	

	float f = 200.0;
	
	if(argc == 2 && atoi(argv[1]) >= 0){
		f = atoi(argv[1]);
	}
	
	int t = 0;
	int tforever = 0;
	
	while(1){
		// Buffer containing n stereo samples (left and right, both 16 bit).		
		int16_t samples[2*BATCH_SIZE];
		unsigned cbBuffer=sizeof(samples);	// size in bytes of sample (4*n bytes)

		while(t<BATCH_SIZE){
			samples[2*t] = 30000*sin(2*M_PI*tforever*f);
			samples[2*t+1] = samples[2*t];
			tforever++;
			t++;
		}
		t = 0;
		
		
		// Read one sample from input
		// Currently there is a lot of overhead here, as we have all the overhead of a system function call,
		// but only get four bytes in return.
		// int got=read(STDIN_FILENO, samples, cbBuffer);
		// if(got<0){
			// fprintf(stderr, "%s : Read from stdin failed, error=%s.", argv[0], strerror(errno));
			// exit(1);
		// }else if(got==0){
			// break;	 // end of file
		// }else if(got!=cbBuffer){
			// fprintf(stderr, "%s : Did not receive expected number of bytes.\n", argv[0]);
			// exit(1);
		// }
		
		// Copy one sample to output
		// And again, a lot of overhead just to get four bytes.
		int done=write(STDOUT_FILENO, samples, cbBuffer);
		if(done<0){
			fprintf(stderr, "%s : Write to stdout failed, error=%s.", argv[0], strerror(errno));
			exit(1);
		}else if(done!=cbBuffer){
			fprintf(stderr, "%s : Could not read requested number of bytes from stream.\n", argv[0]);
		}
		// free(samples);
	}

	return 0;
}
