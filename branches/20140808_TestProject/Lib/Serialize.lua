module(..., package.seeall)

CSerializeHelper  = {}

function CSerializeHelper:new()
    local newInstance = {}
    setmetatable(newInstance,self)
    self.__index = self
    self.m_Serialize = CLuaSerialize()
    return newInstance
end

function CSerializeHelper:SetBuffer(buffer)
    return self.m_Serialize:SetBuffer(buffer)
end

function CSerializeHelper:ToBuffer()
    local r, str = self.m_Serialize:ToBuffer()
    if r then
       return str
    else
        return nil
    end
end

function CSerializeHelper:ReadDWORD()
    local r,n = self.m_Serialize:ReadDWORD()
    if r then
        return n
    else
        return nil
    end
end

function CSerializeHelper:WriteDWORD(n)
    return self.m_Serialize:WriteDWORD(n)
end

function CSerializeHelper:ReadWORD()
    local r,n = self.m_Serialize:ReadWORD()
    if r then
        return n
    else
        return nil
    end
end

function CSerializeHelper:WriteWORD(n)
    return self.m_Serialize:WriteWORD(n)
end

function CSerializeHelper:ReadString()
    local r,n = self.m_Serialize:ReadString()
    if r then
        return n
    else
        return nil
    end
end

function CSerializeHelper:WriteString(n)
    return self.m_Serialize:WriteString(n)
end