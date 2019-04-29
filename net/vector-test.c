#include "my_string.h"
#include "my_vector.h"
#include <string.h>
int main(){
	char *c="hello world";
	char *c2="hello this world";
	MyString *str=my_string_new(c,strlen(c));
	MyString *str2=my_string_new(c2,strlen(c2));
	printf("len %d\n",my_string_len(str));
	MyVector *vec=my_vector_new(sizeof(MyString),my_string_init,my_string_dispose,my_string_copy);;
	my_vector_push_back(vec,str2);
	my_vector_push_back(vec,str);
	my_vector_push_back(vec,str);
	my_vector_push_back(vec,str);
	MyVector *vec2=my_vector_new(sizeof(MyString),my_string_init,my_string_dispose,my_string_copy);
	my_string_unref(str);
	MyString *itor=0;
	int i=0;
	bool equal=0;
	for(itor=my_vector_begin(vec);itor!=my_vector_end(vec);){
		printf("i %d len %d\n",i,my_string_len(itor));
		if(my_string_equal(itor,str2)){
			itor=my_vector_erase(vec,itor);
		}else{
			my_vector_itor_plusplus(vec,itor);
		}
		
		i++;
	}
	
	my_vector_copy(vec2,vec);
	my_string_unref(str2);
	MyVector *vec_vec_string=my_vector_new(sizeof(MyVector),my_vector_init,my_vector_dispose,my_vector_copy);
	my_vector_push_back(vec_vec_string,vec2);
	MyVector *vec3_string=my_vector_new(sizeof(MyVector),my_vector_init,my_vector_dispose,my_vector_copy);
	my_vector_push_back(vec3_string,vec_vec_string);
	my_vector_dtor(vec);
	my_vector_dtor(vec2);
	my_vector_dtor(vec_vec_string);
	my_vector_dtor(vec3_string);
	return 0;
}
