
#ifndef CORTO_CPP_OBJECT_H
#define CORTO_CPP_OBJECT_H

#include <corto/corto.h>
#include <string>

namespace corto {

class Object;
class Object_t;

class CoreApi
{
public:
    friend Object;
    std::string idof();
    Object parentof();
    Object typeof();
private:
    CoreApi(const corto_object ref) : m_ref(ref) {}
    const corto_object m_ref;
};

// C++ base wrapper class
class Object : public CoreApi
{
public:
    friend class Object_fluentAPI;

    Object();
    Object(corto_object ref);
    Object(corto_object ref, void *ptr, corto_type type);
    Object(const Object& obj);
    Object(const Object&& obj);
    Object operator=(Object obj);
    ~Object();

    std::string contentof(std::string contentType);

    CoreApi& corto;
    corto_object ref();
    void* ptr();

protected:
    void ref(corto_object obj);
    void ptr(void* ptr);

private:
    corto_object m_ref; // Reference to object (optional)
    void *m_ptr; // Pointer to value (for objects that live on the stack)
    corto_type m_type;
};

// C++ utility methods that wrap C functions and add exception handling
class Object_fluentAPI {
public:
    corto_object declare(corto_type type);
    corto_object create(corto_type type, void *value);
    corto_object declareChild(corto::Object parent, std::string id, corto_type type);
    corto_object createChild(corto::Object parent, std::string id, corto_type type, void *value);
    void define(void *value);
    void update(void *value);
    void fromcontent(std::string contentType, std::string content);
protected:
    Object_fluentAPI(corto_object ref, void *ptr) : m_ref(ref), m_ptr(ptr) { }
    Object_fluentAPI(void *ptr) : m_ref(NULL), m_ptr(ptr) {}
    corto_type m_type;
    corto_object m_ref; // Reference to object (optional)
    void *m_ptr; // Pointer to value (can be same as object ref)
};

// Helper base class for factories
template <class T>
class Object_fluent : protected Object_fluentAPI
{
public:
    Object_fluent(T& _this, void *ptr) : Object_fluentAPI(ptr), m_this(_this) { }
    Object_fluent(T& _this, corto_object ref, void *ptr) : Object_fluentAPI(ref, ptr), m_this(_this) { }

    T& fromcontent(std::string contentType, std::string content)
      {
          ((Object_fluentAPI*)this)->fromcontent(contentType, content);
          return m_this;
      }
protected:
    T& m_this; // The fluent factory instance (<type>_t)
};

}

#endif
