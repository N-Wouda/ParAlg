//
// Created by Alexandra Vegelien on 04/12/2019.
//

#include "segment.h"
#include "sparse.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



//TODO: Kan dit niet meteen al in readmatrix gebeuren? Of het resultaat weer als matrix opslaan (met een extra kolom)?
//TODO: voor segments samenvoegen is het misschien nutting om begin en eind van nieuwe x waarde bij te houden?
segment_t getSegments(matrix_t mat)
{
    size_t length = mat.length;
    segment_t seg = {mat.x[0], mat.y[0], mat.z[0], mat.z[0]};
    size_t i;
    for(i=1; i < length; i++){
        //Check if still in ongoing segment
        if((mat.x[i] == seg.x) && (mat.y[i] == seg.y) && (mat.z[i] == seg.z2+1)){
            seg.z2++;
        }
        else{ // New segment
            printf("SEGMENT: x: %zu, y: %zu, z1: %zu, z2: %zu\n", seg.x, seg.y, seg.z1, seg.z2);
            seg.x = mat.x[i];
            seg.y = mat.y[i];
            seg.z1 = mat.z[i];
            seg.z2 = mat.z[i];
        }
    }
    printf("SEGMENT: x: %zu, y: %zu, z1: %zu, z2: %zu\n", seg.x, seg.y, seg.z1, seg.z2);

    return seg;
}
