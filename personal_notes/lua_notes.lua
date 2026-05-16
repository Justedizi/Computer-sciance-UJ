-- coments are added with --
--[[
multi line commants are added this way
bla blah
]]

-- printing
print("hello world")
print("concatinate strings : " .. "a " .. "+ " .. "b")

--varibles
local a = 10
local b = nil -- nil is like a null value
print("my number is: " .. a .. "bla blah")
a = false
print(a == b)
-- nil and false are the same

--LOCAL AND GLOBAL SCOPE
--[[
in lua local varibles can only be acces ih current file while global can be form outside GLOBAL VARIBLES ARE DEAFULT
]]
c = 21 --global varible by defult
a = 10
--checkning types of varibles
print(type(c)) -- nubmer
d = tostring(c) -- type conversions
print(math.asin(12)) -- math libery
print(math.random(0, 100)) -- random value form 0 to 100
print(os.time())
local d = "GAGGA"
print(#d .. " thats the length of the string \n", d, "\v")
print(string.len(d) .. "  this works as well")
print(string.lower(d) .. "this is lowered version of " .. d)
print(string.sub(d, 1, 2)) -- substings
print(string.char(65) .. "65 (asci) -> A " .. "and " .. string.byte("B") .. "B (char) -> 66 (asci)")
print("formating strings c syle: " .. string.format("pi :%.2f and my age %i", math.pi, 19))
--many more functins form math and string module will be abelive

--if statemetns
if a > 5 and not (a % 2 == 0) then
	print("a is more then 10 and is NOT divisible by 2")
else
	print("conditions were not met")
	if type(b) == "string" then
		print("b is a string")
	elseif type(b) == "number" then
		print("b is nubmer")
	end
end

--loops
for i = 1, 10, 1 do
	print(i .. "\n")
end
--thats basic syntax iterator , end, step

--reverse order
local start_val, end_val, step_val = 10, 1, -1

for i = start_val, end_val, step_val do
	print(i .. "\n")
end

arr = { 2, 24, 5, 55 } --declaring array

-- interation over arry

for i = 1, #arr do
	print(arr[i])
end

local i = 10

--while loop
while i > 0 do
	print(i .. "\n")
	i = i - 1
end

local j = 4
--repeat unitl loop
repeat
	print("im running !!")
until j >= 0

-- how to get user input

local user_input = io.read()
print(user_input)

local nums = { 12, "some item", 242.52, true }
print(nums) -- you will get something lke this 0x563957353
print(nums[#nums]) -- prints last elemt

-- sort with custom comparioson function

local numbers = { 13, 41254, 12, 13 }
table.sort(numbers, function(num1, num2)
	return (num1 > 2 * num2)
end)

--adding values
table.insert(nums, 3, "aga")
-- table.remove and so on also exist

--functions

function dispaly_age(age)
	age = age or 10 -- if its nil it becomes 18
	print("i am " .. age .. " years old")
end

--function asigmetn to varible diffrent syntax

local sum_and_diff = function(n1, n2)
	return n1 + n2, n1 - n2
end

local _, n2 = sum_and_diff(145, 12) --we can skip one varible with _
print(n2)

--function with unkonwn parameters

local function func2(...)
	print(...)
end

local function sum(...)
	local sum = 0
	for i, v in pairs({ ... }) do
		print(i, v)
		sum = sum + v
	end
	return "sum is: " .. sum
end

print(func2(1, 24, 3))
print(sum(1, 2, 3, 4, 5))

dispaly_age(14)

--corutines are like threads but they are not paralel they are more like cooperative multitasking
local routine_1 = coroutine.create(function()
	for i = 0, 10, 1 do
		print("rotuine 1 : " .. i)
		if i == 5 then
			coroutine.yield() -- this will pause the routine and we can resume it later
		end
	end
end)

local routine_2 = coroutine.create(function()
	for i = 1, 13, 1 do
		print("rotine: 2 " .. i)
	end
end)

coroutine.resume(routine_1) -- this will start the routine 1,2 ... 5 ans suspend
print(coroutine.status(routine_1))
coroutine.resume(routine_2)
coroutine.resume(routine_1) -- this will resume the routine from where it was paused
print(coroutine.status(routine_1)) -- 6,7, .. 10 dead

-- the os module

--time
local past = os.time({ year = 2000, month = 1, day = 1 })
print(os.time() - past)

--env varibles

print(os.getenv("HOME")) --home/justedizi/
--execting bash commands
os.execute("echo hello world") -- this will execute the command in the terminal

-- custom mouule
local mod = require("custom_module")
print(mod.sum(122, 2))

-- OOP in lua

--objects are tables in lua

local obj = { name = "jack", age = 19, list = { time = "14124", random = { 2, 2, 4 } } }

print(obj.name .. " " .. obj.list.random[1])

--functions can also be part of objects
-- self can be used to refer to the object itself
local function pet(n)
	return {
		name = n,
		age = 12.4,
		hungry = true,
		fed = function(self)
			self.hungry = false
		end,
	}
end

local buddy = pet("buddy")
print(buddy.hungry)
buddy:fed() -- methodand self are used together like this
print(buddy.hungry)

--inhreitence can be achieved with metatables

local function Dog(bread)
	local dog = pet("doggo")
	dog.breed = bread
	dog.bark = function(self, sound)
		print(self.breed .. " woof woof " .. sound)
	end
	dog.isLoyal = function(self)
		return self.breed[0] > "d"
	end

	return dog
end

buddy = Dog("labrador")
buddy:bark("afa") -- this will print woof woof

--metatables are tables that can change the behavior of other tables

local metaTable = {
	__add = function(table1, table2)
		local result = {}
		for key, value in pairs(table1) do
			result[key] = value
		end
		for key, value in pairs(table2) do
			result[key] = value
		end
		return result
	end,
}

local tab1 = { 23, 5, 5 }
setmetatable(tab1, metaTable)

print(tab1 + { 123, 12 })

-- look at luaRocks to find lua packages and libraries
