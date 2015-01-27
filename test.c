#include <stdio.h>
#include <stdlib.h>

#include "zll.h"

int main() {
	int i;
	LinkedList ll;
	
	ll = ll_createDynamicCustom(4);
	
	printf("%i\t", ll_put(ll, "Hello,"));
	printf("%i\t", ll_put(ll, "World!"));
	printf("%i\t", ll_put(ll, "This"));
	printf("%i\t", ll_put(ll, "is"));
	printf("%i\t", ll_put(ll, "Scott!"));
	printf("\n");
	
	ll_foreach (ll, i) {
		printf("%i:\t%s\n", i, ll_get(ll, i));
	}
	
	ll_destroy(ll);
	
	return 0;
}
