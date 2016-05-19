/**********************************************************
 * dump_memory.c
 *
 *
 * Author: gaoyu
 * Date Created: 2016/1/29
 * Last Modified by: 2016/1/29
 * Date Last Modified: 2016/1/29
 * Assignment: lab3
 * Part of: lab3
 */ 
   //
    // dump.c
    //

    void dump_memory(void *p, int len)
    {
      int i;
	
	printf("Address          char   hexCh         shor         integer               float         foubleFloat\n");
	
      for (i = 0; i < len; i++) {
    //print memory address
    //0x is 0x
    //%08x
    //0 means pad with zeros if necessary
    //8 means at least 8 characters wide
    // \t is horizontal tab
	        printf("0x%08x\t", p + i);
	//print character with width 3	
	if (((*(unsigned char *)(p + i)) < 32) || ((*(unsigned char *)(p + i)) > 126)) {
		printf("  ?\t");
	}
	else {
	        printf("%3c\t", *(unsigned char *)(p + i));
	}
	//print hexchar
	        printf("0x%02x\t", *(unsigned char *)(p + i));
	
	//print every other short
	if (i % 2 == 0) {
		printf("%+12hd\t", *(short *)(p + i));
	}
	//print every 4th integer
	if (i % 4 == 0) {
		printf("%+12d\t", *(int *)(p + i));
	}
	//print float
	if (i % 4 == 0) {
		printf("\t%+.6e\t", *(float *)(p + i));
	}
	//print double float
    	if (i % 8 == 0) {
	        printf("%+.6e\t", *(double *)(p + i));
	}
	printf("\n");

      }
    }
