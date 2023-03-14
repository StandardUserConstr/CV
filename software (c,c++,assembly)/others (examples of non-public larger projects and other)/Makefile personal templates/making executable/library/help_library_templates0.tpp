//extra
template <typename T> void memset_custom(T* data,const size_t& value,const size_t& count_of_elements)
{
    for(size_t i = 0; i<count_of_elements; i++) *(data+i) = value;
    return;
}
