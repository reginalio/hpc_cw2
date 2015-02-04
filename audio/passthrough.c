#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>

#include <unistd.h>

int main(int argc, char *argv[])
{	

	int n;
	if(argc<2){
		n = 512; 	// Default number of samples
	}else if(atoi(argv[1]) >= 0){
		n = atoi(argv[1]);
	}else{
		fprintf(stderr, "%s : Entered numSamples is negative, error=%s.", argv[0], strerror(errno));
		exit(1);
	}
	

	
	while(1){
		// Buffer containing one stereo sample sample (left and right, both 16 bit).
			// Buffer size 
		int16_t* samples = (int16_t*) malloc (sizeof(samples)*n*2);
		if(samples == NULL) {
			fprintf(stderr, "%s : unable to allocate buffer, error=%s.", argv[0], strerror(errno));
			exit(1);
		}
		
		// int16_t samples[2];
		unsigned cbBuffer=sizeof(samples);	// size in bytes of  one stereo sample (4 bytes)
		
		// Read one sample from input
		// Currently there is a lot of overhead here, as we have all the overhead of a system function call,
		// but only get four bytes in return.
		int got=read(STDIN_FILENO, samples, cbBuffer);
		if(got<0){
			fprintf(stderr, "%s : Read from stdin failed, error=%s.", argv[0], strerror(errno));
			exit(1);
		}else if(got==0){
			break;	 // end of file
		}else if(got!=cbBuffer){
			fprintf(stderr, "%s : Did not receive expected number of bytes.\n", argv[0]);
			exit(1);
		}
		
		// Copy one sample to output
		// And again, a lot of overhead just to get four bytes.
		int done=write(STDOUT_FILENO, samples, cbBuffer);
		if(done<0){
			fprintf(stderr, "%s : Write to stdout failed, error=%s.", argv[0], strerror(errno));
			exit(1);
		}else if(done!=cbBuffer){
			fprintf(stderr, "%s : Could not read requested number of bytes from stream.\n", argv[0]);
		}
		free(samples);
	}

	return 0;
}
