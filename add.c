#include "types.h"
#include "stat.h"
#include "user.h"
	
//passing command line arguments
	
int main(int argc, char** argv)
{   
    if (argc != 3) {
        printf(1, "give 2 integer argumemts");
        exit();
    }
    int x = atoi(argv[1]);
    int y = atoi(argv[2]);
    printf(1, "The sum of the input is %d\n", add(x, y));
    exit();
}

// This code is from GFG for testing 

