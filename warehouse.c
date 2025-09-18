#include "order.h"
#include "bench.h"
#include <stdio.h>
#include <assert.h>

int main(int argc, char **argv) {
	if (argc<2) { printf("Please invoke as %s <order_file>\n",argv[0]); 	return 1; }
	if (!openOrder(argv[1])) { return 1; }
	do {
		int pn=nextPartNumber();
		int bin=pn/10;
		/* Replace the following code with a better implementation */

        static int last_used[5] = {0};   
        static int step = 0;             
        step++;
        int slot = -1;

        for (int s = 0; s < 5; s++) 
        {
            if (binInSlot(s) == bin) 
            {
                slot = s;
                break;
            }
        }

        if (slot == -1) 
        {
            for (int s = 0; s < 5; s++) 
            {
                if (binInSlot(s) == -1) 
                {   
                    slot = s;
                    fetchBin(bin, slot);   
                    break;
                }
            }

        }

        if (slot == -1) 
        {
            int victim = 0;
            for (int s = 1; s < 5; s++) 
            {
                if (last_used[s] < last_used[victim]) 
                victim = s;
            }
            slot = victim;
            fetchBin(bin, slot); 
        }
        last_used[slot] = step;

		/* End of simple implementation */
	} while(fetchNextPart());
	closeOrder();
	return 0;
}
