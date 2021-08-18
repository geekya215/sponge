#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity)
    : _capacity(capacity), _buf_written(0), _buf_read(0), _eof(false), _buf() {
    DUMMY_CODE(capacity);
}

size_t ByteStream::write(const string &data) {
    size_t written = min(remaining_capacity(), data.size());
    for (size_t i = 0; i < written; ++i) {
        _buf.push_back(data[i]);
    }
    _buf_written += written;
    return written;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    size_t l = min(buffer_size(), len);
    return string(_buf.begin(), _buf.begin() + l);
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    size_t l = min(buffer_size(), len);
    for (size_t i = 0; i < l; ++i) {
        _buf.pop_front();
    }
    _buf_read += l;
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    pop_output(len);
    return peek_output(len);
}

void ByteStream::end_input() { _eof = true; }

bool ByteStream::input_ended() const { return _eof; }

size_t ByteStream::buffer_size() const { return _buf.size(); }

bool ByteStream::buffer_empty() const { return _buf.empty(); }

bool ByteStream::eof() const { return _eof && buffer_empty(); }

size_t ByteStream::bytes_written() const { return _buf_written; }

size_t ByteStream::bytes_read() const { return _buf_read; }

size_t ByteStream::remaining_capacity() const { return _capacity - _buf.size(); }
