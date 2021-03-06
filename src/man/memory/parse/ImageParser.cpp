
#include <iostream>
#include <fcntl.h>

#include "ImageParser.h"

namespace man {
namespace memory {
namespace parse {

using namespace std;
using namespace google::protobuf::io;
using boost::shared_ptr;
using namespace include::io;

ImageParser::ImageParser(include::io::FDProvider::const_ptr fdProvider,
        boost::shared_ptr<RoboImage> image) :
        TemplatedParser<RoboImage>(fdProvider, image),
       current_buffer(new const void*),
       current_buffer_size(1),
       finished(false){

    initStreams();
    readHeader();
}

ImageParser::~ImageParser() {
    delete raw_input;
}

void ImageParser::readHeader() {

    this->getNextBuffer();
    uint32_t bytes_read = 0;

    log_header.log_id = this->readValue<int32_t>(&bytes_read);
    cout << "Log ID: " << log_header.log_id << endl;

    log_header.birth_time = this->readValue<int64_t>(&bytes_read);
    cout << "Birth time: " << log_header.birth_time << endl;

    container->setWidth(this->readValue<uint32_t>(&bytes_read));
    container->setHeight(this->readValue<uint32_t>(&bytes_read));
    container->setByteSize(this->readValue<uint32_t>(&bytes_read));
    //the buffer isn't full yet - back up will make sure only the used part
    //is read
    //TODO: bug - the next call to Next() will return @bytes_read less bytes in the buffer
    //find a way around it (using Skip or some other stuff)
    raw_input->BackUp(current_buffer_size - bytes_read);
}

const LogHeader ImageParser::getHeader() {
    return log_header;
}

bool ImageParser::getNext() {

    uint32_t bytes_read = 0;
    this->getNextBuffer();
    if (!finished) {
        container->setTimestamp(this->readValue<int64_t>(&bytes_read));
        container->updateImage(
                reinterpret_cast<const uint8_t*>(*current_buffer) + bytes_read);
    }
    return finished;
}

shared_ptr<const RoboImage> ImageParser::getPrev() {


//    raw_input->BackUp(current_size);
//
//    proto::uint32 size;
//    coded_input->ReadVarint32(&size);
//
//    CodedInputStream::Limit l = coded_input->PushLimit(size);
//    finished = current_message->ParseFromCodedStream(coded_input);
//    coded_input->PopLimit(l);

}

void ImageParser::getNextBuffer() {

    bool notEnd = raw_input->Next(current_buffer, &current_buffer_size);
    finished = !notEnd;
    //we're not guaranteed a non-empty buffer
    //but we're guaranteed one eventually
    while (current_buffer_size == 0 && !finished) {
        raw_input->Next(current_buffer, &current_buffer_size);
    }
}

void ImageParser::initStreams() {

    raw_input = new FileInputStream(fdProvider->getFileDescriptor(),
            container->getByteSize() + sizeof(container->getTimestamp()));
}

}
}
}
