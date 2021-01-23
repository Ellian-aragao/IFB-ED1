#include "copySemRepeticaoLinkedList.h"
#include "../LinkedList/linkedList.h"
#include "../LinkedList/testInterface/testLinkedListInterface.h"

int main()
{
  LinkedList *list1 = testCreateLinkedListWithItensInt(0, 1);
  int a = 2;
  appendLinkedList(list1, &a);
  appendLinkedList(list1, &a);
  appendLinkedList(list1, &a);
  LinkedList *list2 = copySemRepeticaoLinkedList(list1, compareItensInt);
  testForEachPrintItensInt(list1);
  testForEachPrintItensInt(list2);

  destroyLinkedList(list1);
  destroyLinkedList(list2);
  return 0;
}
