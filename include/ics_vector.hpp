/*
We are giving you guiding comments to help you fill out this header file.
The indentation of the comments serve as hints to how your code is structured. 

These are HINTS. PLEASE READ THE README.
Anything not specified here will be in the README.
For example, some functions may be const versions while others may not.
Some functions may throw exceptions while others are noexcept.
*/

/* Preprocessor directives. Guard the header file upon include */
#ifndef ICS_VECTOR_H
#define ICS_VECTOR_H
/*
Which include directives should you put here?
(hint: we may throw VectorExceptions. We also want to use ostream)
*/
#include "vector_exception.hpp"
#include <iosfwd>

/*
Templated Vector class definition with templated Iterator class member
The template type name can be T
*/
template <typename T>
class Vector {

/* Begin by specifying private members of Vector */
private:

    /* We want to nest the Iterator class definition right here */
    class Iterator {

    /* Write out the private members of Iterator */
    private:
        /* there should be an m_container and an index */
        Vector<T>* m_container;
        size_t indx;


    /* Here are our your public members of Iterator*/
    public:
        /* Write your constructors here */
        Iterator(Vector<T>* m_container, size_t indx) : m_container(m_container), indx(indx) {}

        /* Write your operator overloads here.*/
        /* Post and pre increment and decrement operators*/
        Iterator & operator++() {
            if (this->indx >= m_container->size()) {
                throw VectorException("out of bounds");
            }
            (this->indx)++;
            return *this;
        }

        Iterator operator++(int) {
            if (this->indx >= m_container->size()) {
                throw VectorException("out of bounds");
            }
            Iterator temp = *this;
            this->indx++;
            return temp;
        }

        Iterator & operator--() {
            if (this->indx == 0) {
                throw VectorException("out of bounds");
            }
            --(this->indx);
            return *this;
        }

        Iterator operator--(int) {
            if (this->indx == 0) {
                throw VectorException("out of bounds");
            }
            Iterator temp = *this;
            this->indx--;
            return temp;
        }

        /* Overloaded += size_t operator */
        Iterator & operator+=(size_t n) {
            for (size_t i = 0; i < n; ++i){
                ++(*this);
            }
            return *this;
        }

        /* Overloaded -= size_t operator */
        Iterator & operator-=(size_t n) {
            for (size_t i = 0; i < n; ++i) {
                --(*this);
            }
            return *this;
        }

        /* Overloaded - operator. The right hand side is a const Iterator& */
        size_t operator-(const Iterator & other) const {
            if (this->m_container != other.m_container) {
                throw VectorException("iterators point to different containers");
            }
            if (this->indx >= other.indx) {
                return this->indx - other.indx;
            } else {
                return other.indx - this->indx;
            }
        }

        /* Overloaded - operator.  The right hand side is a size_t */
        Iterator operator-(size_t offset) const {
            Iterator temp = *this;
            for (size_t i = 0; i < offset; ++i) {
                --temp;
            }
            return temp;
        }

        /* Overloaded == operator. The right hand side is a const Iterator& */
        bool operator==(const Iterator& other) const noexcept {
            return this->m_container == other.m_container && this->indx == other.indx;
        }

        /* Overloaded != operator. The right hand side is const Iterator& */
        bool operator!=(const Iterator& other) const noexcept {
            return this->m_container != other.m_container || this->indx != other.indx;
        }

        /* Overloaded star (*) operator to dereference. This returns a T& */
        T & operator*() const {
            if (this->indx >= m_container->size()){
                throw VectorException("out of bounds");
            }
            return (*m_container)[this->indx];
        }

        /* Overloaded -> operator. This returns a T* */
        T * operator->() const {
            if (this->indx >= m_container->size()){
                throw VectorException("out of bounds");
            }
            return &((*m_container)[this->indx]);
        }

        /*
        It is correct to add a size_t to an Iterator.
        What keyword should you use to specify these next two overloads? (It's in the README)
        Remember, using + on Iterators is commutative.
        1 + Iterator and Iterator + 1 both return an Iterator that is one forward.
        */
        friend Iterator operator+(size_t n, const Iterator & iter) {
            Iterator temp = iter;
            for (size_t i = 0; i < n; ++i){
                ++temp;
            }
            return temp;
        }

        friend Iterator operator+(const Iterator & iter, size_t n) {
            Iterator temp = iter;
            for (size_t i = 0; i < n; ++i){
                ++temp;
            }
            return temp;
        }

    };

    /* Specify your private Vector member fields. There should be three */
    size_t cap;
    size_t siz;
    T* buffer;


/* You will define your public Vector members here*/
public:
    /* Default constructor */
    Vector() : cap(0), siz(0), buffer(nullptr) {}

    /* An overloaded constructor (see README) */
    Vector(size_t inicap) : cap(inicap), siz(0), buffer(new T[inicap]) {}


    /* The begin() function */
    Iterator begin() noexcept {
        return Iterator(this, 0);
    }

    /* The const version of begin(). Note: it returns a const T* type */
    T const * begin() const noexcept {
        if (this->siz == 0){
            return nullptr;
        }else{
            return this->buffer;
        }
    }

    /* The empty() function */
    bool empty() const noexcept {
        return this->siz == 0;
    }

    /* The end() function */
    Iterator end() noexcept {
        return Iterator(this, this->siz);
    }

    /* The const version of end(). Note: it returns a const T* */
    T const * end() const noexcept {
        if (this->siz == 0){
            return nullptr;
        }else{
            return this->buffer + siz;
        }
    }

    /* The front() function */
    T & front() noexcept {
        return (this->buffer)[0];
    }

    /* The const version of front(). Note it returns a const T& this is different from begin()! */
    T const & front() const noexcept {
        return (this->buffer)[0];
    }



    /* The back() function */
    T & back() noexcept {
        return (this->buffer)[siz - 1];
    }



    /* The const version of back(). Note: it returns a const T& */
    T const & back() const noexcept{
        return (this->buffer)[siz - 1];
    }

    /* The push_back() function */
    void push_back(const T& n) {
        if (this->cap == this->siz){
            if (2 * (this->cap) > 1){
                this->cap *= 2;
            }else{
                this->cap += 1;
            }

            T* newbuffer = new T[cap];
            for (size_t i = 0 ; i < this->siz ; i++ ){
                newbuffer[i] = (this->buffer)[i];
            }

            delete[] this->buffer;
            this->buffer = newbuffer;
        }

        this->buffer[this->siz] = n;
        this->siz++;
    }

    /* The push_back function that takes an RValue reference (Type of T&&) */
    void push_back(T&& n) {
        if (this->cap == this->siz){
            if (2 * (this->cap) > 1){
                this->cap *= 2;
            }else{
                this->cap += 1;
            }
        
            T* newbuffer = new T[cap];
            for (size_t i = 0 ; i < this->siz ; i++ ){
                newbuffer[i] = std::move((this->buffer)[i]);
            }

            delete[] this->buffer;
            this->buffer = newbuffer;
        }

        this->buffer[this->siz] = std::move(n);
        this->siz++;
    }

    /* The pop_back() function*/
    void pop_back() {
        if (this->siz == 0){
            throw VectorException("popping from empty");
        }
        this->siz--;
        (this->buffer)[this->siz].~T();
    }

    /* The capacity() function */
    size_t capacity() const noexcept {
        return this->cap;
    }

    /* The size() function */
    size_t size() const noexcept {
        return this->siz;
    }


    /* The data() function. Returns type T* */
    T * data() noexcept {
        return this->buffer;
    }

    /* The const version of data(). Returns type const T* */
    T const * data() const noexcept {
        return this->buffer;
    }

    /* 
    The erase function. It takes in a start and end Iterator.
    Once again, it is end-exclusive
    Hints for implementation:
        0 1 2 3 4 5
    We want to delete 1 2 3: start points to 1 and end points to 4
        0    1    2    3    4    5
             ^start         ^end
    Replace what is at start with what is at end and advance start and end until it reaches the vec.end()
        0    4    2    3    4    5
                  ^s             ^e
        0    4    5    3    4    5
                       ^s            e=vec.end()
    Is anything after what s is now including s used?
    Hint: resize the vector to include only 0 4 5. You will implement resize anyways.
    */
    void erase(Iterator start, Iterator end) {
        if (start == end) {return;}
        while(end != this->end()){
            *start = *end;
            start++;
            end++;
        }
        this->siz -= (end-start);
    }

    /* swap_elements(). Takes two iterators. Use std::move ! */
    void swap_elements(Iterator lhs, Iterator rhs) noexcept {
        T temp = std::move(*lhs);
        *lhs = std::move(*rhs);
        *rhs = std::move(temp);
    }

    /* Subscript operator[] overload */
    T & operator[](size_t index) noexcept {
        return (this->buffer)[index];
    }

    /* Const version of the subscript operator[] overload */
    T const & operator[](size_t index) const noexcept {
        return (this->buffer)[index];
    }

    /* 
    Overloaded == operator. The right hand side is another const<T>& vector.
    Make sure the sizes of the vectors are equal
    Also check the elements inside are equal.
    */
    bool operator==(const Vector & other) const noexcept {
        if (this->siz == other.size()){
            for (size_t i = 0; i < this->size(); i++){
                if (this->buffer[i] != other.buffer[i]){
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    /* Overloaded != operator. */
    bool operator!=(const Vector & other) const noexcept{
        if (this->siz == other.size()){
            for (size_t i = 0; i < this->siz; i++){
                if (this->buffer[i] != other.buffer[i]){
                    return true;
                }
            }
            return false;
        }
        return true;
    }

    /* Vector copy constructor. Does a deep copy! */
    Vector(const Vector& other) : cap(other.cap), siz(other.siz), buffer(new T[other.cap]) {
        for (size_t i = 0; i < siz; ++i) {
            buffer[i] = other.buffer[i];
        }
    }

    /* 
    Vector assignment operator.
    Make sure you don't leak memory here. 
    */
    Vector& operator=(const Vector& other) {
        if (this == &other) {
            return *this;
        }
        delete[] buffer;
        cap = other.cap;
        siz = other.siz;
        buffer = new T[cap];

        for (size_t i = 0; i < siz; ++i) {
            buffer[i] = other.buffer[i];
        }
        return *this;
    }

    /* at() function. */
    T & at(size_t index) {
        if (this->siz <= index){
            throw VectorException("out of bounds");
        }
        return this->buffer[index];
    }

    /* const version of at() */
    T const & at(size_t index) const {
        if (this->siz <= index){
            throw VectorException("out of bounds");
        }
        return this->buffer[index];
    }

    /* 
    operator<< 
    We want to write code that can write Vectors to an output stream
    like std::cout << v << std::endl;
    You should use the friend keyword somewhere in here. 
    */
    friend std::ostream& operator<<(std::ostream& os, const Vector& other){
        for (size_t i=0; i < other.size(); i++){
            os << other.data()[i] << ' ';
        }
        return os;
    }

    /*
    Vector resize() function here.
    Allocate a new buffer to move all the old elements from the old one to.
    And then assign that new buffer to the `this`
    Make sure to use std::move() to move data from the old buffer to the new one.
    Make sure you don't leak memory!
    */
    void resize(size_t new_capacity) {
        if (new_capacity == this->cap) {return;}
        this->cap = new_capacity;
        this->siz = new_capacity;
        T* newbuffer = new T[new_capacity];
        for (size_t i = 0; i < (this->siz); i++){
            newbuffer[i] = std::move((this->buffer)[i]);
        }

        delete[] this->buffer;
        this->buffer = newbuffer;
    }

    /*
    clear() function. Make sure the destructor of each element gets called.
    delete[] will automatically do this. 
    But there other ways of implementing this function.
    */
    void clear() noexcept {
        for (size_t i=0; i < this->siz; i++) {
            this->buffer[i].~T();
        }
        this->siz = 0;
    }

    /* Move constructor here */
    Vector(Vector&& other) noexcept : cap(other.cap), siz(other.siz), buffer(other.buffer) {
        other.cap = 0;
        other.siz = 0;
        other.buffer = nullptr;
    }

    /* 
    Move assignment here
    Make sure there are not memory leaks!
    */
    Vector& operator=(Vector&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        delete[] buffer;
        this->cap = other.cap;
        this->siz = other.siz;
        this->buffer = other.buffer;
        other.cap = 0;
        other.siz = 0;
        other.buffer = nullptr;
        return *this;
    }

    /* The Vector destructor goes here. Make sure there are no leaks */
    ~Vector() noexcept {
        delete[] buffer;
    }
};
/* 
And we are finished with this header file! 
If you used an #ifndef #define, what should you add at the very end?
*/
#endif
