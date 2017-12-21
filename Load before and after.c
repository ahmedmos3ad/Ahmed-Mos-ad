fscanf(ptrB,"%[^,],%[^,],%[^,],%d,%[^,],%d,%[^,],%d,%d\n",book[counter].title,book[counter].author,book[counter].publisher,
                   &book[counter].D.year,book[counter].D.month,&book[counter].D.day,book[counter].category,book[counter].copies,book[counter].currentCopies);

                   fscanf(ptrB,"%[^,]",&book[counter].title);
