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

// These helpers let Compartment::wrap() identify Composite objects and
// extract their key without depending on a full Composite implementation.
// In a real engine the key would be the sorted property list; here it is
// a plain string for the POC.
bool IsCompositeObject(JSObject* obj);
JSString* GetCompositeKey(JSObject* obj);
JSObject* NewCompositeObject(JSContext* cx, JS::HandleString key);

[[nodiscard]] bool MakeComposite(JSContext* cx, unsigned argc, JS::Value* vp);
[[nodiscard]] bool IsCompositeShell(JSContext* cx, unsigned argc, JS::Value* vp);

}  // namespace js

#endif  // builtin_Composite_h
