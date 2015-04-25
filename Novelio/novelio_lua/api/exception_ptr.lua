
--------------------------------
-- @module exception_ptr
-- @parent_module nv

--------------------------------
-- 
-- @function [parent=#exception_ptr] __cxa_exception_type 
-- @param self
-- @return std::type_info#std::type_info ret (return value: std::type_info)
        
--------------------------------
-- 
-- @function [parent=#exception_ptr] operator= 
-- @param self
-- @param #std::__exception_ptr::exception_ptr 
-- @return std::__exception_ptr::exception_ptr#std::__exception_ptr::exception_ptr ret (return value: std::__exception_ptr::exception_ptr)
        
--------------------------------
-- 
-- @function [parent=#exception_ptr] swap 
-- @param self
-- @param #std::__exception_ptr::exception_ptr 
        
--------------------------------
-- @overload self, NULL         
-- @overload self         
-- @overload self, ??         
-- @function [parent=#exception_ptr] exception_ptr
-- @param self
-- @param #?? __o

return nil
