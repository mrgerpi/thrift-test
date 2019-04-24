/**
 * Autogenerated by Thrift Compiler (0.9.2)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef thrift_test_kernal_TYPES_H
#define thrift_test_kernal_TYPES_H

#include <iosfwd>

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include <thrift/cxxfunctional.h>


namespace thrift_test_kernal {

struct ServiceType {
  enum type {
    Client = 0,
    Server = 1
  };
};

extern const std::map<int, const char*> _ServiceType_VALUES_TO_NAMES;

class GetServiceListRequest;

class GetServiceListResponse;

class AddServiceRequest;

class AddServiceResponse;

class FillDataRequest;

class FillDataResponse;

class RequestTriggerRequest;

class RequestTriggerReseponse;


class GetServiceListRequest {
 public:

  static const char* ascii_fingerprint; // = "8BBB3D0C3B370CB38F2D1340BB79F0AA";
  static const uint8_t binary_fingerprint[16]; // = {0x8B,0xBB,0x3D,0x0C,0x3B,0x37,0x0C,0xB3,0x8F,0x2D,0x13,0x40,0xBB,0x79,0xF0,0xAA};

  GetServiceListRequest(const GetServiceListRequest&);
  GetServiceListRequest& operator=(const GetServiceListRequest&);
  GetServiceListRequest() : type((ServiceType::type)0) {
  }

  virtual ~GetServiceListRequest() throw();
  ServiceType::type type;

  void __set_type(const ServiceType::type val);

  bool operator == (const GetServiceListRequest & rhs) const
  {
    if (!(type == rhs.type))
      return false;
    return true;
  }
  bool operator != (const GetServiceListRequest &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const GetServiceListRequest & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const GetServiceListRequest& obj);
};

void swap(GetServiceListRequest &a, GetServiceListRequest &b);


class GetServiceListResponse {
 public:

  static const char* ascii_fingerprint; // = "B8D94EBFFE99C6E7010418EB2DF36DC3";
  static const uint8_t binary_fingerprint[16]; // = {0xB8,0xD9,0x4E,0xBF,0xFE,0x99,0xC6,0xE7,0x01,0x04,0x18,0xEB,0x2D,0xF3,0x6D,0xC3};

  GetServiceListResponse(const GetServiceListResponse&);
  GetServiceListResponse& operator=(const GetServiceListResponse&);
  GetServiceListResponse() : errorCode(0) {
  }

  virtual ~GetServiceListResponse() throw();
  int32_t errorCode;
  std::vector<std::string>  instanceList;

  void __set_errorCode(const int32_t val);

  void __set_instanceList(const std::vector<std::string> & val);

  bool operator == (const GetServiceListResponse & rhs) const
  {
    if (!(errorCode == rhs.errorCode))
      return false;
    if (!(instanceList == rhs.instanceList))
      return false;
    return true;
  }
  bool operator != (const GetServiceListResponse &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const GetServiceListResponse & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const GetServiceListResponse& obj);
};

void swap(GetServiceListResponse &a, GetServiceListResponse &b);


class AddServiceRequest {
 public:

  static const char* ascii_fingerprint; // = "EC8C8E8D6042A67E4AF0F04DA3F39A73";
  static const uint8_t binary_fingerprint[16]; // = {0xEC,0x8C,0x8E,0x8D,0x60,0x42,0xA6,0x7E,0x4A,0xF0,0xF0,0x4D,0xA3,0xF3,0x9A,0x73};

  AddServiceRequest(const AddServiceRequest&);
  AddServiceRequest& operator=(const AddServiceRequest&);
  AddServiceRequest() : type((ServiceType::type)0), serviceName(), version(), idlAbsFileName() {
  }

  virtual ~AddServiceRequest() throw();
  ServiceType::type type;
  std::string serviceName;
  std::string version;
  std::string idlAbsFileName;

  void __set_type(const ServiceType::type val);

  void __set_serviceName(const std::string& val);

  void __set_version(const std::string& val);

  void __set_idlAbsFileName(const std::string& val);

  bool operator == (const AddServiceRequest & rhs) const
  {
    if (!(type == rhs.type))
      return false;
    if (!(serviceName == rhs.serviceName))
      return false;
    if (!(version == rhs.version))
      return false;
    if (!(idlAbsFileName == rhs.idlAbsFileName))
      return false;
    return true;
  }
  bool operator != (const AddServiceRequest &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const AddServiceRequest & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const AddServiceRequest& obj);
};

void swap(AddServiceRequest &a, AddServiceRequest &b);


class AddServiceResponse {
 public:

  static const char* ascii_fingerprint; // = "E86CACEB22240450EDCBEFC3A83970E4";
  static const uint8_t binary_fingerprint[16]; // = {0xE8,0x6C,0xAC,0xEB,0x22,0x24,0x04,0x50,0xED,0xCB,0xEF,0xC3,0xA8,0x39,0x70,0xE4};

  AddServiceResponse(const AddServiceResponse&);
  AddServiceResponse& operator=(const AddServiceResponse&);
  AddServiceResponse() : errorCode(0) {
  }

  virtual ~AddServiceResponse() throw();
  int32_t errorCode;

  void __set_errorCode(const int32_t val);

  bool operator == (const AddServiceResponse & rhs) const
  {
    if (!(errorCode == rhs.errorCode))
      return false;
    return true;
  }
  bool operator != (const AddServiceResponse &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const AddServiceResponse & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const AddServiceResponse& obj);
};

void swap(AddServiceResponse &a, AddServiceResponse &b);


class FillDataRequest {
 public:

  static const char* ascii_fingerprint; // = "EC8C8E8D6042A67E4AF0F04DA3F39A73";
  static const uint8_t binary_fingerprint[16]; // = {0xEC,0x8C,0x8E,0x8D,0x60,0x42,0xA6,0x7E,0x4A,0xF0,0xF0,0x4D,0xA3,0xF3,0x9A,0x73};

  FillDataRequest(const FillDataRequest&);
  FillDataRequest& operator=(const FillDataRequest&);
  FillDataRequest() : type((ServiceType::type)0), serviceName(), methodName(), data() {
  }

  virtual ~FillDataRequest() throw();
  ServiceType::type type;
  std::string serviceName;
  std::string methodName;
  std::string data;

  void __set_type(const ServiceType::type val);

  void __set_serviceName(const std::string& val);

  void __set_methodName(const std::string& val);

  void __set_data(const std::string& val);

  bool operator == (const FillDataRequest & rhs) const
  {
    if (!(type == rhs.type))
      return false;
    if (!(serviceName == rhs.serviceName))
      return false;
    if (!(methodName == rhs.methodName))
      return false;
    if (!(data == rhs.data))
      return false;
    return true;
  }
  bool operator != (const FillDataRequest &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const FillDataRequest & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const FillDataRequest& obj);
};

void swap(FillDataRequest &a, FillDataRequest &b);


class FillDataResponse {
 public:

  static const char* ascii_fingerprint; // = "E86CACEB22240450EDCBEFC3A83970E4";
  static const uint8_t binary_fingerprint[16]; // = {0xE8,0x6C,0xAC,0xEB,0x22,0x24,0x04,0x50,0xED,0xCB,0xEF,0xC3,0xA8,0x39,0x70,0xE4};

  FillDataResponse(const FillDataResponse&);
  FillDataResponse& operator=(const FillDataResponse&);
  FillDataResponse() : errorCode(0) {
  }

  virtual ~FillDataResponse() throw();
  int32_t errorCode;

  void __set_errorCode(const int32_t val);

  bool operator == (const FillDataResponse & rhs) const
  {
    if (!(errorCode == rhs.errorCode))
      return false;
    return true;
  }
  bool operator != (const FillDataResponse &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const FillDataResponse & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const FillDataResponse& obj);
};

void swap(FillDataResponse &a, FillDataResponse &b);


class RequestTriggerRequest {
 public:

  static const char* ascii_fingerprint; // = "07A9615F837F7D0A952B595DD3020972";
  static const uint8_t binary_fingerprint[16]; // = {0x07,0xA9,0x61,0x5F,0x83,0x7F,0x7D,0x0A,0x95,0x2B,0x59,0x5D,0xD3,0x02,0x09,0x72};

  RequestTriggerRequest(const RequestTriggerRequest&);
  RequestTriggerRequest& operator=(const RequestTriggerRequest&);
  RequestTriggerRequest() : serviceName(), methodName() {
  }

  virtual ~RequestTriggerRequest() throw();
  std::string serviceName;
  std::string methodName;

  void __set_serviceName(const std::string& val);

  void __set_methodName(const std::string& val);

  bool operator == (const RequestTriggerRequest & rhs) const
  {
    if (!(serviceName == rhs.serviceName))
      return false;
    if (!(methodName == rhs.methodName))
      return false;
    return true;
  }
  bool operator != (const RequestTriggerRequest &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const RequestTriggerRequest & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const RequestTriggerRequest& obj);
};

void swap(RequestTriggerRequest &a, RequestTriggerRequest &b);


class RequestTriggerReseponse {
 public:

  static const char* ascii_fingerprint; // = "3F5FC93B338687BC7235B1AB103F47B3";
  static const uint8_t binary_fingerprint[16]; // = {0x3F,0x5F,0xC9,0x3B,0x33,0x86,0x87,0xBC,0x72,0x35,0xB1,0xAB,0x10,0x3F,0x47,0xB3};

  RequestTriggerReseponse(const RequestTriggerReseponse&);
  RequestTriggerReseponse& operator=(const RequestTriggerReseponse&);
  RequestTriggerReseponse() : errorCode(0), reqponseJson() {
  }

  virtual ~RequestTriggerReseponse() throw();
  int32_t errorCode;
  std::string reqponseJson;

  void __set_errorCode(const int32_t val);

  void __set_reqponseJson(const std::string& val);

  bool operator == (const RequestTriggerReseponse & rhs) const
  {
    if (!(errorCode == rhs.errorCode))
      return false;
    if (!(reqponseJson == rhs.reqponseJson))
      return false;
    return true;
  }
  bool operator != (const RequestTriggerReseponse &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const RequestTriggerReseponse & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const RequestTriggerReseponse& obj);
};

void swap(RequestTriggerReseponse &a, RequestTriggerReseponse &b);

} // namespace

#endif
