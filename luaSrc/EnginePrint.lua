function EngineLog(...)
  -- Iterate over all passed arguments and print them using the original function
  local args = {...}
  message = ""
  for i, v in ipairs(args) do
    -- You can modify arguments here (e.g., format them)
    message = message .. v
  end
  print("[Lua LOG] " .. os.date("%H:%M:%S"), message)
end

return Script