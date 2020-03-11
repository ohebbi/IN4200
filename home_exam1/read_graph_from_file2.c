// Opens a text file, allocates two vectors and
// reads the web graph in a compressed row storage format.
// This function follows the 0-indices convention, but can
// easily be transformed into 1-indices convention.
//
// Parameters
// ----------
// filename: char
// N, N_links: initialized ints
// row_ptr, col_idx: initialized vectors of ints

void read_graph_from_file2(char *filename, int *N, int *N_links, int **row_ptr, int **col_idx){

    FILE *file = fopen(filename, "r");

    //skipping lines
    fscanf(file, "%*[^\n]\n");
    fscanf(file, "%*[^\n]\n");

    //reading number of webpages and links.
    fscanf(file, "# Nodes: %d Edges: %d\n", &*N, &*N_links);
    fscanf(file, "%*[^\n]\n");

    (*N)++;   //row_ptr is of size N+1.
    int *fromNodeId; int *toNodeId;
    int fromNode; int toNode;

    alloc1D(col_idx, *N_links);

    alloc1D(row_ptr, *N);

    alloc1D(&fromNodeId,*N_links);
    alloc1D(&toNodeId,*N_links);

    fscanf(file,"%d %d", &fromNode, &toNode);
    int validcounts = 0;
    int totalcounts = 0;
    //read file and store every fromNode and toNode to each vector.
    while (!feof (file)){
        if (fromNode != toNode){
            fromNodeId[validcounts] = fromNode;
            toNodeId[validcounts] = toNode;
            validcounts++;
        }

        fscanf(file,"%d %d", &fromNode, &toNode);

        totalcounts++;
    }
    printf("# of self-links: %d\n", (totalcounts-validcounts));
    *N_links -= (totalcounts-validcounts);

    // The next for-loops shows how to make a CRS out of fromNodeId and toNodeId.
    for (int i = 0; i < *N_links; i++){
        (*row_ptr)[toNodeId[i]]++;
    }

    int sum = 0;
    for (int i = 0; i < *N; i++){
        int tmp       = (*row_ptr)[i];
        (*row_ptr)[i] = sum;
        sum          += tmp;
    }
    (*row_ptr)[*N] = *N_links;

    for (int i = 0; i < *N_links; i++){
        int row  = toNodeId[i];
        int dest = (*row_ptr)[row];

        (*col_idx)[dest] = fromNodeId[i];
        (*row_ptr)[row] ++;
    }

    int last = 0;
    for (int i = 0; i <= *N; i++){
        int tmp       = (*row_ptr)[i];
        (*row_ptr)[i] = last;
        last = tmp;
    }

    //follow the convention with an extra zero in the beginning.
    //0-indices convention. Add +1 for 1-indices convention for the row pointers

    /* Delete this if there should not be a zero with no reason in the beginning etc 0,0,1,4,..
    for (int i = *N; i >= 1; i--){
        (*row_ptr)[i] = (*row_ptr)[i-1] ; // +1
    }
    (*row_ptr)[0] = 0;
    */


    //uncomment for 1-indices convention for the column indices.
    /*
    for (int i = 0; i<*N_links; i++){
      (*col_idx)[i] += 1;
    }
    */

    //printf("col_idx:\n");
    //printvec(*col_idx,*N_links);
    //printf("row_ptr:\n");
    //printvec(*row_ptr,*N);

    free(fromNodeId); free(toNodeId);
}
