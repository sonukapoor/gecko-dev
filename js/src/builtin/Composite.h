/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef builtin_Composite_h
#define builtin_Composite_h

#include "js/TypeDecls.h"

namespace js {

// Placeholder Composite class for the TC39 Composites POC.
// Stores a single key string in reserved slot 0.
extern const JSClass CompositeClass;

// Returns true if obj was created with CompositeClass.
bool IsCompositeObject(JSObject* obj);

// Returns the key string stored in slot 0. obj must be a Composite.
JSString* GetCompositeKey(JSObject* obj);

// Creates a new Composite in the current compartment with the given key.
JSObject* NewCompositeObject(JSContext* cx, JS::HandleString key);

// Shell-exposed functions.
bool MakeComposite(JSContext* cx, unsigned argc, JS::Value* vp);
bool IsCompositeShell(JSContext* cx, unsigned argc, JS::Value* vp);

}  // namespace js

#endif  // builtin_Composite_h
