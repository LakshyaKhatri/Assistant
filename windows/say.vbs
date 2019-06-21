set s = CreateObject("SAPI.SpVoice") 
s.Speak Wscript.Arguments(0),2
s.WaitUntilDone(1000)