/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "builtin/Composite.h"

#include "js/CallArgs.h"
#include "js/Class.h"
#include "js/Conversions.h"
#include "vm/JSObject.h"
#include "vm/NativeObject.h"
#include "vm/StringType.h"

using namespace js;

const JSClass js::CompositeClass = {
    "Composite",
    JSCLASS_HAS_RESERVED_SLOTS(1),
};

bool js::IsCompositeObject(JSObject* obj) {
  return obj->hasClass(&CompositeClass);
}

JSString* js::GetCompositeKey(JSObject* obj) {
  MOZ_ASSERT(IsCompositeObject(obj));
  return obj->as<NativeObject>().getReservedSlot(0).toString();
}

JSObject* js::NewCompositeObject(JSContext* cx, JS::HandleString key) {
  JS::RootedObject obj(cx,
                       NewObjectWithGivenProto(cx, &CompositeClass, nullptr));
  if (!obj) {
    return nullptr;
  }
  obj->as<NativeObject>().setReservedSlot(0, JS::StringValue(key));
  return obj;
}

bool js::MakeComposite(JSContext* cx, unsigned argc, JS::Value* vp) {
  JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
  if (!args.requireAtLeast(cx, "makeComposite", 1)) {
    return false;
  }

  JS::RootedString key(cx, JS::ToString(cx, args[0]));
  if (!key) {
    return false;
  }

  JS::RootedObject obj(cx, NewCompositeObject(cx, key));
  if (!obj) {
    return false;
  }

  args.rval().setObject(*obj);
  return true;
}

bool js::IsCompositeShell(JSContext* cx, unsigned argc, JS::Value* vp) {
  JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
  if (!args.requireAtLeast(cx, "isComposite", 1)) {
    return false;
  }

  args.rval().setBoolean(args[0].isObject() &&
                         IsCompositeObject(&args[0].toObject()));
  return true;
}
