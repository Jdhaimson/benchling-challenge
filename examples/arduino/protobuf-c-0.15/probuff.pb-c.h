/* Generated by the protocol buffer compiler.  DO NOT EDIT! */

#ifndef PROTOBUF_C_probuff_2eproto__INCLUDED
#define PROTOBUF_C_probuff_2eproto__INCLUDED

#include <protobuf-c.h>

PROTOBUF_C_BEGIN_DECLS


typedef struct _ProBuff__MyMessage ProBuff__MyMessage;


/* --- enums --- */


/* --- messages --- */

struct  _ProBuff__MyMessage
{
  ProtobufCMessage base;
  char *registration_key;
  int32_t device_id;
  size_t n_data;
  char **data;
  size_t n_binary_data;
  ProtobufCBinaryData *binary_data;
};
#define PRO_BUFF__MY_MESSAGE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&pro_buff__my_message__descriptor) \
    , NULL, 0, 0,NULL, 0,NULL }


/* ProBuff__MyMessage methods */
void   pro_buff__my_message__init
                     (ProBuff__MyMessage         *message);
size_t pro_buff__my_message__get_packed_size
                     (const ProBuff__MyMessage   *message);
size_t pro_buff__my_message__pack
                     (const ProBuff__MyMessage   *message,
                      uint8_t             *out);
size_t pro_buff__my_message__pack_to_buffer
                     (const ProBuff__MyMessage   *message,
                      ProtobufCBuffer     *buffer);
ProBuff__MyMessage *
       pro_buff__my_message__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   pro_buff__my_message__free_unpacked
                     (ProBuff__MyMessage *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*ProBuff__MyMessage_Closure)
                 (const ProBuff__MyMessage *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor pro_buff__my_message__descriptor;

PROTOBUF_C_END_DECLS


#endif  /* PROTOBUF_probuff_2eproto__INCLUDED */
