/****************************************************************************
 * Filename: main.c
 * Original Author: Faith E. Olusegun (propenster)
 * File Creation Date: December 5th, 2023
 * Description: C implementation of the novel abstract data structure, Book
 * LICENSE: MIT
 *************************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct Page {
    int data; // for a hypothetical data of type int...
    struct Page* parent;
    struct Page* child;
    bool isParentPage;
    bool isLastPage;
} Page;

typedef struct {
    Page value;
    Page* parent;
    Page* child;
} PageItem;

Page* create_page(int data) {
    Page* page_item = (Page*)malloc(sizeof(Page));
    if (page_item == NULL) {
        return NULL;
    }
    page_item->data = data;
    page_item->parent = NULL;
    page_item->child = NULL;

    return page_item;
}

/// <summary>
/// init a new Book data structure...
///
///
///</summary>
Page* init_(int data, Page* parent_page, Page* child_page) {
    Page* page_item = (Page*)malloc(sizeof(Page));
    if (page_item != NULL) {
        page_item->data = data;
        if (parent_page != NULL) {
            page_item->parent = parent_page;
            page_item->isParentPage = false;
        }
        else {
            page_item->parent = NULL;
            page_item->isParentPage = true;
        }

        if (child_page != NULL) {
            page_item->child = child_page;
        }
        else {
            page_item->child = NULL;
            page_item->isLastPage = true;
        }
    }

    return page_item;
}

void print_page_item(Page* page_item) {
    if (page_item != NULL) {
        printf("{\nPage Item: %d\n Parent: %d\n Child: %d\n} \n", page_item->data,
            page_item->parent->data, page_item->child->data);
    }
}
/**
Flip a page to the left i.e expose the child of this current page...

current POinter is now set as the child and this currentPointer becomes parent,
child of the new Page is NULL.

*/
Page* flip(Page* item) {

    if (item == NULL) {
        return NULL;
    }

    if (item->child == NULL) {
        /*new_item->data = item->data;
        new_item->child = NULL;
        new_item->parent = item->parent;*/
        return item; // this page is the last page
    }

    Page* new_item = (Page*)malloc(sizeof(Page));

    // flip to next page...
    new_item->data = item->child->data;
    new_item->parent = item;
    new_item->child = NULL;

    free(item->child);


    return new_item;
}
/**
This erases the content of a current PageItem... It's like using a
correction pen on just a single page.

This means, the Parent Page and the Child Page of this CurrentPage are left
intact.

*/
void erase_page(Page* page_item) {
    if (page_item != NULL) {
        page_item->data = 0; // erase value in page...
    }
}
/**This is like tearing away a page of paper. It has two sides, this current
   PagetItem and it's Child page (nextPage) - a sheet of paper has two faces.

  */
void delete_page(Page* page_item) {
    page_item->child = NULL; // delete page...
    page_item->data = 0;
}
/**
Check if a Pageitem is blank/empty...
Meaning have we used a correction pen on some page and it's now not containing
any data, though there is still references to it's parent and child...
  */
bool is_blank(PageItem* item) { return true; }

void bookTransversal(Page* page_item) {
    if (page_item != NULL) {
        bookTransversal(page_item->parent);
        printf("%d ", page_item->data);
        bookTransversal(page_item->child);
    }
}

void freePage(Page* page_item) {
    if (page_item != NULL) {
        freePage(page_item->parent);
        freePage(page_item->child);
        free(page_item);
    }
}

Page* add_page(Page* page_item, int data) {
    if (page_item == NULL) {
        return create_page(data);
    }
    //page_item->parent = add_page(page_item->parent, page_item->data);
    page_item->child = add_page(page_item->child, data);

    return page_item;
}

int main(void) {
    printf("Hello World\n");

    Page* page = NULL;
    // page = init_(10, NULL, NULL);
    page = add_page(page, 20);
    add_page(page, 30);
    add_page(page, 40);
    add_page(page, 50);
    bookTransversal(page);
    //print_page_item(page);

    page = flip(page);
    printf("New Parent data: %d\n", page->parent->data);
    printf("Next Page data: %d\n", page->data);
    //print_page_item(page);

    freePage(page);

    return 0;
}