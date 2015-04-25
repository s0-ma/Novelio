
--------------------------------
-- @module Ref
-- @parent_module nv

--------------------------------
-- Releases the ownership immediately.<br>
-- This decrements the Ref's reference count.<br>
-- If the reference count reaches 0 after the descrement, this Ref is<br>
-- destructed.<br>
-- see retain, autorelease<br>
-- js NA
-- @function [parent=#Ref] release 
-- @param self
        
--------------------------------
-- Retains the ownership.<br>
-- This increases the Ref's reference count.<br>
-- see release, autorelease<br>
-- js NA
-- @function [parent=#Ref] retain 
-- @param self
        
--------------------------------
-- Returns the Ref's current reference count.<br>
-- returns The Ref's reference count.<br>
-- js NA
-- @function [parent=#Ref] getReferenceCount 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- Releases the ownership sometime soon automatically.<br>
-- This descrements the Ref's reference count at the end of current<br>
-- autorelease pool block.<br>
-- If the reference count reaches 0 after the descrement, this Ref is<br>
-- destructed.<br>
-- returns The Ref itself.<br>
-- see AutoreleasePool, retain, release<br>
-- js NA<br>
-- lua NA
-- @function [parent=#Ref] autorelease 
-- @param self
-- @return Ref#Ref ret (return value: cc.Ref)
        
return nil
