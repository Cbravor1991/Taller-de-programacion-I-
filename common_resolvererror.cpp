// Copyright 2023 martinp.dipaola@gmail.com
#include "common_resolvererror.h"

#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>

ResolverError::ResolverError(int gai_errno) : gai_errno(gai_errno) { }

const char* ResolverError::what() const noexcept {
    return gai_strerror(gai_errno);
}

ResolverError::~ResolverError() {}
