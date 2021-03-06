/*
 * Copyright (c) 1997, 2020, Oracle and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 *
 */

#include "precompiled.hpp"
#include "jfr/jfrEvents.hpp"
#include "jvm.h"
#include "memory/allocation.inline.hpp"
#include "oops/oop.inline.hpp"
#include "runtime/arguments.hpp"
#include "runtime/globals.hpp"
#include "runtime/globals_extension.hpp"
#include "runtime/globals_shared.hpp"
#include "runtime/flags/jvmFlagConstraintList.hpp"
#include "runtime/os.hpp"
#include "runtime/sharedRuntime.hpp"
#include "utilities/defaultStream.hpp"
#include "utilities/macros.hpp"
#include "utilities/ostream.hpp"
#include "utilities/stringUtils.hpp"

// Implementation macros
#define MATERIALIZE_PRODUCT_FLAG(type, name, value, doc)      type name = value;
#define MATERIALIZE_PD_PRODUCT_FLAG(type, name, doc)          type name = pd_##name;
#define MATERIALIZE_DIAGNOSTIC_FLAG(type, name, value, doc)   type name = value;
#define MATERIALIZE_PD_DIAGNOSTIC_FLAG(type, name, doc)       type name = pd_##name;
#define MATERIALIZE_EXPERIMENTAL_FLAG(type, name, value, doc) type name = value;
#define MATERIALIZE_MANAGEABLE_FLAG(type, name, value, doc)   type name = value;
#define MATERIALIZE_PRODUCT_RW_FLAG(type, name, value, doc)   type name = value;
#ifdef PRODUCT
#define MATERIALIZE_DEVELOPER_FLAG(type, name, value, doc)
#define MATERIALIZE_PD_DEVELOPER_FLAG(type, name, doc)
#define MATERIALIZE_NOTPRODUCT_FLAG(type, name, value, doc)
#else
#define MATERIALIZE_DEVELOPER_FLAG(type, name, value, doc)    type name = value;
#define MATERIALIZE_PD_DEVELOPER_FLAG(type, name, doc)        type name = pd_##name;
#define MATERIALIZE_NOTPRODUCT_FLAG(type, name, value, doc)   type name = value;
#endif // PRODUCT
#ifdef _LP64
#define MATERIALIZE_LP64_PRODUCT_FLAG(type, name, value, doc) type name = value;
#else
#define MATERIALIZE_LP64_PRODUCT_FLAG(type, name, value, doc) /* flag is constant */
#endif // _LP64


ALL_FLAGS(MATERIALIZE_DEVELOPER_FLAG,     \
          MATERIALIZE_PD_DEVELOPER_FLAG,  \
          MATERIALIZE_PRODUCT_FLAG,       \
          MATERIALIZE_PD_PRODUCT_FLAG,    \
          MATERIALIZE_DIAGNOSTIC_FLAG,    \
          MATERIALIZE_PD_DIAGNOSTIC_FLAG, \
          MATERIALIZE_EXPERIMENTAL_FLAG,  \
          MATERIALIZE_NOTPRODUCT_FLAG,    \
          MATERIALIZE_MANAGEABLE_FLAG,    \
          MATERIALIZE_PRODUCT_RW_FLAG,    \
          MATERIALIZE_LP64_PRODUCT_FLAG,  \
          IGNORE_RANGE,                   \
          IGNORE_CONSTRAINT)
