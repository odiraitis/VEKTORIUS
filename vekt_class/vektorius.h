#define pragma once
#include <initializer_list>
#include <algorithm>
#include <iterator>
#include <exception>
#include <memory>
#include <cstddef>
#include <utility>

template<class T,class Alloc = std::allocator<T>> class Vector {
public:
    
    typedef T value_type;
    typedef Alloc allocator_type;
    typedef size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef value_type&reference;
    typedef const value_type& const_reference;
    typedef typename std::allocator_traits<allocator_type>::pointer pointer;
    typedef typename std::allocator_traits<allocator_type>::const_pointer const_pointer;
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    
    // konstruktoriai
    
    explicit Vector(const allocator_type& alloc = allocator_type()) :
    allocator_(alloc),
    capacity_(0),
    size_(0),
    array_(nullptr)
    {
        rearrange_pointers();
        
    };
    //copy
    Vector(const Vector& temp) :
    allocator_(),
    capacity_(temp.capacity()),
    size_(temp.size()),
    array_(allocator_.allocate(temp.capacity()))
    {
        rearrange_pointers();
        construct_elements(temp.begin(), temp.end(), array_start_);
  
    };
    //move
    Vector(Vector&& temp) :
    allocator_(),
    capacity_(temp.capacity_),
    size_(temp.size_),
    array_(temp.array_)
    {
        rearrange_pointers();
        temp.array_ = nullptr;
        temp.size_ = 0;
        temp.capacity_ = 0;
        temp.rearrange_pointers();
    };
    //destruktorius
    
   ~Vector() {
        naikink(array_, size_);
        allocator_.deallocate(array_, capacity_);
        array_start_ = nullptr;
        array_end_ = nullptr;
        array_range_end_ = nullptr;
    }
    
    // = operatorius
  Vector& operator=(Vector&& temp)
    {
        naikink(array_, capacity_);
        allocator_.deallocate(array_, capacity_);
        size_ = temp.size_;
        capacity_ = temp.capacity_;
        array_ = temp.array_;
        rearrange_pointers();
        temp.size_ = 0;
        temp.capacity_ = 0;
        temp.array_ = nullptr;
        temp.rearrange_pointers();
        return *this;
    }
    // assign
    
    void assign(size_type n, const_reference val) {
        if (n > capacity_) { increase_array(n); }
        construct_elements(array_, n, val);
        size_ = n;
        rearrange_pointers();
        //std::cout << "assign 1" << std::endl;
    }
    
    void assign(pointer first, pointer last) {
        if (last - first > capacity_) { increase_array(last - first); }
        construct_elements(first, last, array_start_);
        size_ = last - first;
        rearrange_pointers();
        //std::cout << "assign 2" << std::endl;
    }
    
    void assign(std::initializer_list<value_type> il) {
        if (il.size() <= capacity_) {
        }
        else {
            increase_array(il.size());
        }
        construct_elements(il.begin(), il.end(), begin());
        size_ = il.size();
        rearrange_pointers();
        //std::cout << "assign 3" << std::endl;
    }
    

    // get_allocator
    
   inline allocator_type get_allocator() { return allocator_; }
    
    // ELEMENT ACCESS
    
    // at
    
   reference at(size_type n)
    {
        if (n >= 0 && n < capacity_){ return *(array_start_ + n); }
        else throw std::out_of_range("out of vector range.");
    }
    
    const_reference at(size_type n) const
    {
        if (n >= 0 && n < capacity_){ return *(array_start_ + n); }
        else throw std::out_of_range("out of vector range.");
    }
    
    // operator []
    
    reference operator[](size_type n) { return *(array_start_ + n); }
    
    const_reference operator[](size_type n) const { return *(array_start_ + n); }
    
    // front
    
    inline reference front() { return *(array_start_); }
    
    inline const_reference front() const { return *(array_start_); }
    
    // back
    
    inline reference back() { return *(array_end_); }
    
    inline const_reference back() const { return *(array_end_); }
    
    // data
    
    inline pointer data() const { return array_; }
    
    // begin end iteratoriai
    
    inline iterator begin() { return iterator(array_start_); }
    
    inline const_iterator begin() const { return const_iterator(array_start_); }
    
    inline const_iterator cbegin() const { return const_iterator(array_start_); }
    
    inline iterator end() { return iterator(array_end_); }
    
    inline const_iterator end() const { return const_iterator(array_end_); }
    
    inline const_iterator cend() const { return const_iterator(array_end_); }
    
    inline reverse_iterator rbegin() { return reverse_iterator(end()); }
    
    inline const_reverse_iterator rbegin() const { return reverse_iterator(cend()); }
    
    inline const_reverse_iterator crbegin() const { return reverse_iterator(cend()); }
    
    inline reverse_iterator rend() { return reverse_iterator(begin()); }
    
    inline const_reverse_iterator rend() const { return reverse_iterator(cbegin()); }
    
    inline const_reverse_iterator crend() const { return reverse_iterator(cbegin()); }
    
    //vektoriaus dydis
    
    inline bool empty() const { return size_ == 0; }
    
    inline size_type size() const { return size_; }
    
    inline size_type max_size() const { return size_type(-1); }
    
    void reserve(size_type n)
    {
        if (n > capacity_){ increase_array(n); }
    }
    
    inline size_type capacity() const { return capacity_; }
    
    void shrink_to_fit() { increase_array(size_); }
 
    // vektoriaus valymas
    
    void clear()
    {
        naikink(array_, size_);
        size_ = 0;
        rearrange_pointers();
    }
    // insert
    
    iterator insert(const_iterator position, const value_type& val)
    {
        const difference_type distance = position - cbegin();
        if (array_end_ == array_range_end_)
        {
            increase_array(std::max(1, static_cast<int>(capacity_ * 2)));
        }
        size_++;
        iterator it = begin() + distance;
        construct_elements_backward(it, end(), array_start_ + distance + 1);
        allocator_.construct(array_start_ + distance, val);
        rearrange_pointers();
        return it;
    }
    
    iterator insert(const_iterator position, value_type&& val)
    {
        const difference_type distance = position - cbegin();
        if (array_end_ == array_range_end_)
        {
            increase_array(std::max(1, static_cast<int>(capacity_ * 2)));
        }
        size_++;
        iterator it = begin() + distance;
        construct_elements_backward(it, end(), array_start_ + distance + 1);
        allocator_.construct(array_start_ + distance, val);
        rearrange_pointers();
        return it;
    }
    
    iterator insert(const_iterator position, size_type count, const value_type& val)
    {
        const difference_type distance = position - cbegin();
        if (size_ + count > capacity_)
        {
            increase_array(std::max(static_cast<int>(capacity_ * 2), static_cast<int>(size_ + count)));
        }
        size_ += count;
        iterator it = begin() + distance;
        construct_elements_backward(it, end(), array_start_ + distance + count);
        construct_elements(it, count, val);
        rearrange_pointers();
        return it;
    }
    
    iterator insert(const_iterator position, const_iterator first, const_iterator last)
    {
        const difference_type distance = position - cbegin();
        const difference_type count = last - first;
        if (size_ + count > capacity_)
        {
            increase_array(std::max(static_cast<int>(capacity_ * 2), static_cast<int>(size_ + count)));
        }
        size_ += count;
        iterator it = begin() + distance;
        construct_elements_backward(it, end(), array_start_ + distance + count);
        construct_elements(first, last, array_start_ + distance);
        rearrange_pointers();
        return it;
    }
    
    iterator insert(const_iterator position, std::initializer_list<value_type> il)
    {
        const difference_type distance = position - cbegin();
        const difference_type count = il.end() - il.begin();
        if (size_ + count > capacity_)
        {
            increase_array(std::max(static_cast<int>(capacity_ * 2), static_cast<int>(size_ + count)));
        }
        size_ += count;
        iterator it = begin() + distance;
        construct_elements_backward(it, end(), array_start_ + distance + count);
        construct_elements(il.begin(), il.end(), array_start_ + distance);
        rearrange_pointers();
        return it;
    }
    
    // emplace
    
   template <class... Args>
    iterator emplace(const_iterator position, Args&&... args)
    {
        difference_type distance = position - cbegin();
        if (array_end_ == array_range_end_)
        {
            increase_array(std::max(1, static_cast<int>(capacity_ * 2)));
        }
        construct_elements_backward(begin() + distance, end(), array_start_ + distance + 1);
        allocator_.construct(array_start_ + distance, std::forward<Args>(args)...);
        size_++;
        rearrange_pointers();
        return begin() + distance;
    }
    
    // erase reikalingas atrinkimui su remove if
 
    iterator erase(const_iterator first, const_iterator last)
    {
        const difference_type distance = first - cbegin();
        const difference_type distance_first_last = last - cbegin();
        iterator it_first = begin() + distance;
        iterator it_last = begin() + distance_first_last;
        construct_elements(it_last, end(), array_start_ + distance);
        size_ -= last - first;
        rearrange_pointers();
        return it_first;
        
    }
    
    // push_back
    
    void push_back(const value_type& val)
    {
        if (array_end_ == array_range_end_)
        {
            increase_array(std::max(1, static_cast<int>(capacity_ * 2)));
        }
        allocator_.construct(array_end_, val);
        size_++;
        rearrange_pointers();
    }
    
    // pop_back
    
    void pop_back()
    {
        allocator_.destroy(array_end_);
        size_--;
        rearrange_pointers();
    }
    
    // resizinimas
    void resize(size_type n)
    {
        if (n <= size_)
        {
            naikink(array_start_ + n, size_ - n);
        }
        else increase_array(std::max(n, 2 * capacity_));
        size_ = n;
    }
    
    void resize(size_type n, const value_type& val)
    {
        if (n <= size_)
        {
            naikink(array_start_ + n, size_ - n);
        }
        else
        {
            increase_array(std::max(n, 2 * capacity_));
            construct_elements(end(), array_range_end_ - array_end_, val);
            rearrange_pointers();
        }
        size_ = n;
    }
//swapas
    void swap(Vector& temp)
    {
        std::swap(capacity_, temp.capacity_);
        std::swap(size_, temp.size_);
        std::swap(array_, temp.array_);
        rearrange_pointers();
        temp.rearrange_pointers();
    }

private:
    allocator_type allocator_;
    size_type capacity_;
    size_type size_;
    pointer array_;
    pointer array_start_;
    pointer array_end_;
    pointer array_range_end_;
    
    void rearrange_pointers()
    {
        array_start_ = array_;
        array_end_ = array_ + size_;
        array_range_end_ = array_ + capacity_;
    }
    
    void increase_array(size_type new_size)
    {
        pointer new_array = allocator_.allocate(new_size);
        construct_elements(begin(), std::min(end(), begin() + new_size), new_array);
        
        naikink(array_, size_);
        allocator_.deallocate(array_, capacity_);
        array_ = new_array;
        capacity_ = new_size;
        rearrange_pointers();
    }
    void construct_elements(const_iterator begin, const_iterator end, const_iterator destination)
    {
        const difference_type distance = end - begin;
        //std::cout << "c_elem 1 " << std::endl;
        for (difference_type i = 0; i < distance; ++i)
        {
            allocator_.construct(destination +i, *(begin));
            begin++;
        }
    }
    
    void construct_elements_backward(const_iterator begin, const_iterator end, const_iterator destination)
    {
        
        const difference_type distance = end - begin;
        for (difference_type i = distance - 1; i >= 0; --i)
        {
            allocator_.construct(destination + i, *(end - 1));
            end--;
        }
    }
    
    void construct_elements(pointer destination, size_type count, value_type value)
    {
        for (size_type i = 0; i < count; ++i)
        {
            allocator_.construct(destination + i, value);
        }
    }
    
    void naikink(pointer start, size_type n)
    {
        for (size_type i = 0; i < n; ++i)
        {
            allocator_.destroy(start + i);
        }
    }
};
