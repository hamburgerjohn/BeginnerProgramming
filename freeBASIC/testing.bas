dim alpha(0 to 25) As Integer

dim length As Integer 

length = 65

For index As Integer = LBound(alpha) to UBound(alpha)
    alpha(index) = length
    length = length + 1
Next

dim morse(0 to 25) As String

morse(0) = "10 "
morse(1) = "0111 "
morse(2) = "0101 "
morse(3) = "011 "
morse(4) = "1 "
morse(5) = "1101 "
morse(6) = "001 "
morse(7) = "1111 "
morse(8) = "11 "
morse(9) = "1000 "
morse(10) = "010 "
morse(11) = "1011 "
morse(12) = "00 "
morse(13) = "01 "
morse(14) = "000 " 
morse(15) = "1001 "
morse(16) = "0010 "
morse(17) = "101 "
morse(18) = "111 "
morse(19) = "0 "
morse(20) = "110 "
morse(21) = "1110 "
morse(22) = "100 "
morse(23) = "0110 "
morse(23) = "0100 "
morse(24) = "0011 "

dim in As String
in = "HELLO my name is gay"

dim in_fixed As String

in_fixed = UCASE(in)

dim num As Integer

For index As Integer = 0 to len(in_fixed)-1

    num = ASC(MID(In_fixed, index + 1, 1))
    if num = 32 then
        print(" ")
    else
        print(morse(num-65))
    end if

Next




