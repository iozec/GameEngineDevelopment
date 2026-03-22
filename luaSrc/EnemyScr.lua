dofile("./../luaSrc/EnginePrint.lua")

Script = {
}

test = 0
function Script.Update()

    --custom_print("Test: ", test )

    --print("[lua] component updateing")
    --EngineLog(""..parentObject.Transform.Location.x)
    parentObject.Transform.Location.x = parentObject.Transform.Location.x -1
    --EngineLog(""..parentObject.Transform.Location.x)
    test = test + 1
    --EngineLog("Test:"..test)
end

return Script