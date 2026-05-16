-- most baisc syntax for module
T = {}
--two ways to create functions inside module

T.dummmyummy = function(a)
	print("this is a dummy function" .. a)
end

function T.sum(n1, n2)
	return n1 + n2
end

return T
