// Copyright 2016 Yahoo Inc. Licensed under the terms of the Apache 2.0 license. See LICENSE in the project root.
#include <vespa/fastos/fastos.h>
#include <vespa/document/bucket/bucketid.h>
#include "feedstate.h"
#include <vespa/log/log.h>
LOG_SETUP(".feedstate");

using document::BucketId;
using vespalib::IllegalStateException;
using vespalib::make_string;

namespace proton {

void FeedState::throwExceptionInReceive(const vespalib::string &docType,
                                        uint64_t serialRangeFrom,
                                        uint64_t serialRangeTo,
                                        size_t packetSize) {
    throw IllegalStateException
        (make_string("We should not receive any packets from"
                     " the transaction log when in '%s' feed state:"
                     " doctype(%s),"
                     " packetSerialRange(%" PRIu64 ",%" PRIu64 "),"
                     " packetSize(%zu)",
                     getName().c_str(),
                     docType.c_str(),
                     serialRangeFrom, serialRangeTo,
                     packetSize));
}

void
FeedState::throwExceptionInHandleOperation(const vespalib::string &docType,
                                           const FeedOperation &op)
{
    throw IllegalStateException
        (make_string("We should not receive any feed operations"
                     " when in '%s' feed state:"
                     " doctype(%s),"
                     " serial(%" PRIu64 ")",
                     getName().c_str(),
                     docType.c_str(),
                     op.getSerialNum()));
}

vespalib::string FeedState::getName() const {
    switch(_type) {
    case NORMAL:
        return "NORMAL";
    case REPLAY_TRANSACTION_LOG:
        return "REPLAY_TRANSACTION_LOG";
    case INIT:
        return "INIT";
    }
    return "Unknown";
}

}  // namespace proton
