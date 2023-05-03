#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>


int Find(int* parent, int x) {
    if (parent[x] == x) {
        return x;
    }
    else {
        return parent[x] = Find(parent, parent[x]);
    }
}

void Union(int* parent, int x, int y) {
    int parentX = Find(parent, x);
    int parentY = Find(parent, y);
	if (parentY != parentX){
    	parent[parentY] = parentX;
	}
}

int main() {
    int countHair, countReq, loveNum;
    scanf("%d %d %d", &countHair, &countReq, &loveNum);
    int* parent = (int*)malloc(countHair * sizeof(int));
    int* hairLong = (int*)malloc(countHair * sizeof(int));
    int countCut = countHair - 1;
    for (int i = 0; i < countHair; ++i) {
        parent[i] = i;
        hairLong[i] = 0;
    }
    for (int i = 0; i < countHair; ++i) {
        scanf("%d", &hairLong[i]);
        if (hairLong[i] < loveNum && i - 1 >= 0 && hairLong[i - 1] < loveNum) {
            Union(parent,i - 1, i);
            countCut -= 1;
        }
    }
    for (int i = 0; i < countReq; ++i) {
        int status, idHair, plusLong;
        scanf("%d", &status);
        if (status == 1) {
            scanf("%d %d", &idHair, &plusLong);
            hairLong[idHair - 1] += plusLong;
            if (hairLong[idHair - 1] - plusLong <= loveNum && hairLong[idHair - 1] > loveNum) {
                parent[idHair - 1] = idHair - 1;
                countCut += 1;
                if (idHair - 2 >= 0 && hairLong[idHair - 2] > loveNum) {
                    Union(parent, idHair - 2, idHair - 1);
                    countCut -= 1;
                }
                if (idHair < countHair && hairLong[idHair] > loveNum) {
                    Union(parent, idHair, idHair - 1);
                    countCut -= 1;
                }
            }
        }
        else {
            printf("%d\n", countCut);
        }
    }
    return 0;
}