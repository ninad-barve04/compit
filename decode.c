#include <stdio.h>
#include <string.h>

#include "encode.h"
#include "decode.h"
#include "constants.h"

void decode_file(FILE *encoded, FILE *decoded) {
    ProbabilityDistribution pd;
    memset(pd.range, 0, sizeof(pd.range));

    unsigned char bitList[BUFFER_SIZE];

    for (int i = 0; i < BUFFER_SIZE; i++) {
        fread(&(bitList[i]), sizeof(unsigned char), 1, encoded);
        fread(&(pd.range[i]), sizeof(unsigned short), 1, encoded);
    }

    long double encoded_value;
    fread(&encoded_value, sizeof(long double), 1, encoded);
    int count_of_characters;
    fread(&count_of_characters, sizeof(unsigned long), 1, encoded);

    // for (int i = 0; i < BUFFER_SIZE; i++) {
    //     printf("%hx\t\t%hx\n", bitList[i], pd.range[i]);
    // }
    printf("%.34Lg , %d\n",encoded_value,  count_of_characters);
    pd.cumulative_prob = count_of_characters;
    pd.lower = 0.0;
    pd.upper = 1.0;

    double current_range = 1.0;
    
    double low = 0.0;
    double high = 0.0;
    int i =0;
    while (count_of_characters != 0) {
        
        //current_range = pd.upper - pd.lower + 1;
        //encoded_value = (encoded_value - pd.lower) + 1;
        //encoded_value = (encoded_value * pd.cumulative_prob) / current_range;
        //printf("%lf , %lf, %ld, \n", pd.lower , pd.upper, pd.cumulative_prob);

        for (int i = 0; i < BUFFER_SIZE; i++) {
            // printf("Inside for loop\n");
           
           
            if (i == 0) {
                low = pd.lower;
                high = pd.lower + pd.range[i] * (current_range/pd.cumulative_prob);
                if (encoded_value >= 0.0 && encoded_value < high ) {
                  //  printf("%hx\n", i);
                    printf("Lower:%lf\t Upper:%lf %Lg\n", low, high, encoded_value);
                    fwrite(&i, sizeof(unsigned char), 1, decoded);
                    pd.upper = high;
                    break;
                }
                
            } else {
                low = pd.lower + pd.range[i-1] * (current_range/(double)pd.cumulative_prob);
                high = pd.lower + pd.range[i] * (current_range/(double)pd.cumulative_prob);
                
                if (encoded_value >= low && encoded_value < high) {
                 //   printf("%hx\n", i);
                    printf("%d %d\tLower:%.19g\t Upper:%.19g %.19Lg\n", i, pd.range[i],low, high, encoded_value);
                    fwrite(&i, sizeof(unsigned char), 1, decoded);
                    pd.upper = high;
                    pd.lower = low;
                    break;
                }
            }
          
            
            
        }
        current_range = ( pd.upper - pd.lower);
      //  printf("%lf , %lf, %ld, \n", pd.lower , pd.upper, pd.cumulative_prob);
        
        // i++;
        // if( i == 7)
        //     break;
        count_of_characters--;
    }
    
    /*
    unsigned short current_range = 0;
    int count_of_characters = 0;
    while ((byte = fgetc(ip_fp)) != EOF) {
        current_range = pd.upper - pd.lower + 1;
        pd.upper = pd.lower + ((current_range * pd.range[(unsigned char) byte]) / pd.cumulative_prob) - 1;
        pd.lower = pd.lower + ((current_range * pd.range[(unsigned char) (byte - 1)]) / pd.cumulative_prob);
        count_of_characters++;
    }
    */

    return;
}