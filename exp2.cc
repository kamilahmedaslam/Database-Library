#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

int main()
{
    char character;
    int random;

    // Construct records for testing
    Record record;
    for (int i = 0; i < 100; i++)
    {
        char *attribute = (char *)malloc(attribute_size + 1);
        attribute[0] = '\0';
        for (int j = 0; j < 10; j++)
        {
            random = rand() % 26;
            character = 'a' + random;
            int size = strlen(attribute);
            attribute[size] = character;
            attribute[size + 1] = '\0';
        }
        record.push_back(attribute);
    }

    int size = fixed_len_sizeof(&record);
    printf("fixed_len_sizeof(record) returned %d, expected 100*10=1000\n", size);

    void *buf = malloc(size);
    Page page;
    
    init_fixed_len_page(&page, 10000, size);
    
    printf("page capacity: %d\n", fixed_len_page_capacity(&page));


    printf("%d\n", add_fixed_len_page(&page, &record));
    printf("page free slots: %d\n", fixed_len_page_freeslots(&page));

    Record record2;
    //printf("%s\n", ((char *)page.data)[0]);
    printf("%d\n", add_fixed_len_page(&page, &record));
    printf("page free slots: %d\n", fixed_len_page_freeslots(&page));

    read_fixed_len_page(&page, 0, &record);


    fixed_len_write(&record, buf);
    
    fixed_len_read(buf, size, &record2);
    printf("Record in buf: %s, Record deserialized and written in record: %s\n", record[0], record2[0]);
    printf("Record in buf: %s, Record deserialized and written in record: %s\n", record[87], record2[87]);
}