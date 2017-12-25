#ifndef POINTER_H_PP_
#define POINTER_H_PP_

 class Pointer{
 
 public:
 	/*The copy constructor takes a reference to a const parameter. 
 	It is const to guarantee that the copy constructor doesn't change it,
 	and it is a reference because a value parameter would require making a copy,
 	which would invoke the copy constructor, 
 	which would make a copy of its parameter,
 	which would invoke the copy constructor, which ...*/
 	Pointer(){}
 	Pointer(const Pointer& p);
 	
 	int x,y;
 
 };
 
#endif
