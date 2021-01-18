void MPI_Alltoall_a(int rank,int size,int tag){  //

        int index,source;

        char message[100];

        char buffers[ProNum][100];//if buffers *[100],there will be errors.

        char buffer[10];

        MPI_Status status;

        strcpy(message,"Hello,the message is from process ");

        //message="Hello,the message is from process ";

        snprintf(buffer,10,"%d",rank);

        strcat(message,buffer);

        for(index=0;index<size;index++){

                MPI_Send(message,strlen(message), MPI_CHAR, index, tag, MPI_COMM_WORLD); /*sending data to node#1*/

        }

        printf("There are %d processes in the group.\n",size);

        for(source=0;source<size;source++){

                MPI_Recv(buffers[source],100, MPI_CHAR,source, tag, MPI_COMM_WORLD, &status);

                printf("Process %d received %s\n",rank,buffers[source]);

        }

}