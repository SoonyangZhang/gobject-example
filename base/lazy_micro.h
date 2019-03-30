#define lazy_is_obj(ns,type,obj) (ns##_IS_##type(obj))
#define lazy_is_class(ns,type,kclass) (ns##_IS_##type##_CLASS(kclass))
