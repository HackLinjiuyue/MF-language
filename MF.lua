   			yxj={}
   			zero='~0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKMLMOPQRSTUVWXYZ_'
   			yxj['<']=4
   			yxj['>']=4
   			yxj['!']=4
   			yxj['=']=4
   			yxj['&']=2
   			yxj['|']=3
   			yxj['+']=5
   			yxj['-']=5
   			yxj['/']=6
   			yxj['*']=6
   			yxj['^']=7
   			yxj['#']=7
   			yxj['$']=9
   			yxj['.']=8
   			yxj['@']=11
   			yxj[',']=10
   	set_nonstruct={"def",'fun','let','out','deffun','return'}
	set_struct={'if','rep','return','else','endif','endrep'}
	value={}
	valuename={}
   	symbol='+-*/^#$!=><|&.,@'
   	err={}
	out=""
	errorcount=0
	file=io.open('test.mfs','r')
	io.input(file)
	all_code=io.read("*a")
	io.close()
	file=nil
	function getmin(n1,n2)
		if(n1<n2)
			then
			return n1
		else
			return n2
		end
	end
	function calculate(valu)
		    local stack={}
   			local last={''}
   			local la=1
   			local ca=1
   			local sa=0
   			local key=''
		local valuecount=2
		while(valuecount<string.len(valu)+1)
			do
			key=key..string.sub(valu,valuecount,valuecount)
			valuecount=valuecount+1
			end
		if(valu=='nil')
   			then
   			return nil
   elseif(valu=='true')
   		then
   		return true
   elseif(valu=='false')
   		then
   		return false
   elseif(value[valu]~=nil)
   	then
   	return value[valu]
		else
   			while(ca<string.len(valu)+1)
   				do
   				s=string.sub(valu,ca,ca)
   				if(isins(s,zero)==true)
   					then
   					last[la]=last[la]..s
   				elseif(s=='(')
   					then
   					sa=sa+1
   					stack[sa]=s
   				elseif(s==')')
   					then
   					while(stack[sa]~='(')
   						do
   						la=la+1
   						last[la]=''
   						last[la]=last[la]..stack[sa]
   						stack[sa]=nil
   						sa=sa-1
   					end
   					stack[sa]=nil
   					sa=sa-1
   			elseif(isins(s,symbol)==true)
   					then
   					la=la+1
   					last[la]=''
   					local yxj1=yxj[s]
   					local yxj2=yxj[stack[sa]]
   					if(yxj2==nil)
   						then
   						yxj2=0
   					end
   					if(yxj1==nil)
   						then
   						yxj1=0
   					end
   					if(yxj1>yxj2)
   					then
   					sa=sa+1
   					stack[sa]=s
   				else
   					while(yxj2>=yxj1)
   						do
   						last[la]=last[la]..stack[sa]
   						la=la+1
   						last[la]=''
   						stack[sa]=nil
   						sa=sa-1
   						yxj2=yxj[stack[sa]]
   						if(yxj2==nil)
   							then
   							yxj2=0
   						end
   					end
   					sa=sa+1
   					stack[sa]=s
   				end
   			end
   				ca=ca+1
			end
			while(stack[sa]~=nil)
				do
				la=la+1
				last[la]=''
				last[la]=last[la]..stack[sa]
				stack[sa]=nil
				sa=sa-1
			end
			ca=1
			local num='0123456789'
			while(ca<la+1)
				do
				if(isins(string.sub(last[ca],1,1),zero)==true)
					then
					sa=sa+1
					if(isins(string.sub(last[ca],1,1),num)==true)
						then
						stack[sa]=tonumber(last[ca])
					elseif(string.sub(last[ca],1,1)=='~')
						then
						stack[sa]=string.sub(last[ca],2,string.len(last[ca]))
					else
						stack[sa]=value[last[ca]]
					end
				else
					if(isins(last[ca],symbol)==true)
						then
						local op=last[ca]
					if(op=='$')
						then
							stack[sa]=stack[sa]*-1
							sa=sa+1
					elseif(op=='.')
						then
						stack[sa-1]=stack[sa-1][last[ca-1]]
					elseif(op==',')
						then
						stack[sa-1]=stack[sa-1]..','..stack[sa]
					elseif(op=='@')
						then
						local ar=1
						local valuetable={''}
						local mode=stack[sa-1].arguments
						local v=1
						while(ar<string.len(stack[sa])+1)
							do
							local s=string.sub(stack[sa],ar,ar)
							if(s~=',')
								then
								valuetable[v]=valuetable[v]..s
							else
								valuetable[v]=calculate(valuetable[v])
								v=v+1
								valuetable[v]=''
							end
							ar=ar+1
						end
						local ar=1
						while(ar<mode.len+1)
							do
							value[mode[ar]]=calculate(valuetable[ar])
							ar=ar+1
						end
						stack[sa-1]=calculate(explainer(stack[sa-1].code))
						local ar=1
						while(ar<mode.len+1)
							do
							value[mode[ar]]=nil
							ar=ar+1
						end
					elseif(op=='+')
							then
							if(type(stack[sa-1])=='string'and type(stack[sa])=='string')
								then
							stack[sa-1]=stack[sa-1]..stack[sa]
							elseif(type(stack[sa-1])=='number'and type(stack[sa])=='number')
								then
							stack[sa-1]=stack[sa-1]+stack[sa]
						else
							return '数字不能与字符串或其他类型的数值相加'
						end
					elseif(op=='-')
							then
							stack[sa-1]=stack[sa-1]-stack[sa]
					elseif(op=='*')
							then
							stack[sa-1]=stack[sa-1]*stack[sa]
					elseif(op=='/')
							then
							if(stack[sa]~=0)
								then
							stack[sa-1]=stack[sa-1]/stack[sa]
						else
							return '0不能作为被除数'
						end
					elseif(op=='^')
							then
							stack[sa-1]=stack[sa-1]^stack[sa]
					elseif(op=='#')
							then
							if(stack[sa]%2==0)
								then
							if(stack[sa-1]<0)
								then
								return '负数不能被开偶次方根'
							else
								stack[sa-1]=stack[sa-1]^(1/stack[sa])
							end
							else
								if(stack[sa-1]<0)
									then
									stack[sa-1]=-1*math.abs(stack[sa-1])^(1/stack[sa])
								else
								stack[sa-1]=stack[sa-1]^(1/stack[sa])
							end
							end
					elseif(op=='>')
							then
							stack[sa-1]=stack[sa-1]>stack[sa]
					elseif(op=='<')
							then
							stack[sa-1]=stack[sa-1]<stack[sa]
					elseif(op=='=')
							then
							stack[sa-1]=stack[sa-1]==stack[sa]
					elseif(op=='!')
							then
							stack[sa-1]=stack[sa-1]~=stack[sa]
					elseif(op=='|')
							then
							stack[sa-1]=stack[sa-1]or stack[sa]
					elseif(op=='&')
							then
							stack[sa-1]=stack[sa-1]and stack[sa]
							
						end
						sa=sa-1
					end
				end
				ca=ca+1
			end
			return stack[1]
		end
	end
	function identfy_struct(codebox,l)
			local i=1
			while(i<l)
				do

		end
	end
	function identfy_nonstruct(code)--识别非嵌套语句
		--语法规则:
		--def:def a value 
		--out:out value
		if(code[1]=='def')
			then
			value[code[2]]=calculate(code[3])
	elseif(code[1]=='out')
			then
				if(code[2]=='console')
				then
				print(calculate(code[3]))
			else
				errorcount=errorcount+1
				err[errorcount]=(pa+i-1)..'：目标<'..code[2]..'>不在可使用的范围内'
			end
	elseif(code[1]=='let')
		then
		if(value[code[2]]==nil)
			then
			errorcount=errorcount+1
			err[errorcount]=(pa+i-1)..'：变量<'..code[2]..'>未定义'
		else
			value[code[2]]=calculate(code[3])
		end
	else
	return false
			end
	end
function isin(s,arr,len)--检查器用
	local isa=1
	while(isa<len+1)
		do
		if(arr[isa]==s)
			then
			return true
		end
		isa=isa+1
	end
	return false
end
function isins(str,arr)
	local isa=1
	while(isa<string.len(arr)+1)
		do
		if(string.sub(arr,isa,isa)==str)
			then
			return true
		else
			isa=isa+1
		end
	end
			return false
end
function outstack(stackn,len)
	local isa=1
	local out=''
	while(isa<len+1)
		do
		out=out..stackn[isa]..','
		isa=isa+1
	end
	return out
	end
function parseCode(text)
	local temp={{''}}
	local ac=1
	local pa=1
	local ta=1
	while(ac<string.len(text)+1)
		do
		s=string.sub(text,ac,ac)
		if(s==' ')
			then
			pa=pa+1
			temp[ta][pa]=''
		elseif(s==';')
			then
			ta=ta+1
			temp[ta]={''}
			pa=1
		elseif(s=='\n')
			then
		else
			temp[ta][pa]=temp[ta][pa]..s
		end
		ac=ac+1
	end
	temp.len=ta
	return temp
end
function explainer(on_code)--解释器主函数
	local pa=1
	while(pa<on_code.len+1)
		do
		if(isin(on_code[pa][1],set_nonstruct,7)==true)
			then
			if(on_code[pa][1]=='def')
				then
				value[on_code[pa][2]]=calculate(on_code[pa][3])
			elseif(on_code[pa][1]=='deffun')
				then
				local temp={}
				local te=0
				local fun_a=1
				local p=pa
				while(fun_a>0)
					do
					if(fun_a==0)
						then
						break
					end
					pa=pa+1
					te=te+1
					temp[te]=on_code[pa]
					if(on_code[pa][1]=='endfun')
					then
					fun_a=fun_a-1
					elseif(on_code[pa][1]=='deffun')
						then
						fun_a=fun_a+1
				end
				end
				if(fun_a~=0)
					then
					errorcount=errorcount+1
					err[errorcount]=pa..'；错误：所定义的函数<'..on_code[p][2]..'>缺少结束标识<endfun>'
				else
					value[on_code[p][2]]={}
					value[on_code[p][2]].code=temp
					value[on_code[p][2]].type='function'
					value[on_code[p][2]].code.len=te
					if(on_code[p][3]~=nil)
						then
						local temp={''}
						local te=1
						local se=1
						while(se<string.len(on_code[p][3])+1)
							do
							local s=string.sub(on_code[p][3],se,se)
							if(s~=',')
								then
								temp[te]=temp[te]..s
							else
								te=te+1
								temp[te]=''
							end
							se=se+1
					end
					if(temp[te]=='')
						then
						errorcount=errorcount+1
						err[errorcount]=p..'：错误：所定义的函数<'..on_code[p][2]..'>的参数格式不正确'
					end
					value[on_code[p][2]].arguments=temp
					value[on_code[p][2]].arguments.len=te
				end
			end
		elseif(on_code[pa][1]=='return')
			then
			return calculate(on_code[pa][2])
		elseif(on_code[pa][1]=='out')
			then
			if(on_code[pa][2]=='console')
				then
				print(calculate(on_code[pa][3]))
			else
				errorcount=errorcount+1
				err[errorcount]=pa..'：目标<'..on_code[pa][2]..'>不在可使用的范围内'
			end
			elseif(on_code[pa][1]=='let')
				then
				if(value[on_code[pa][2]]==nil)
					then
			errorcount=errorcount+1
			err[errorcount]=pa..'：变量<'..on_code[pa][2]..'>未定义'
				else
					value[on_code[pa][2]]=calculate(on_code[pa][3])
				end
			end
			elseif(isin(on_code[pa][1],set_struct,6)==true)
				then
				local main_stack={}
				local main_sa=0
				local endif_a=0
				local endrep_a=0
				local toa=0
				local re=0
				local if_a=0
				while(pa<on_code.len+1)
				do
				toa=toa+1
				main_stack[toa]=on_code[pa]
				if(main_stack[toa][1]=='if')
					then
					if_a=if_a+1
				elseif(main_stack[toa][1]=='rep')
					then
					re=re+1
				elseif(main_stack[toa][1]=='endif')
					then
					endif_a=endif_a+1
				elseif(main_stack[toa][1]=='endrep')
					then
					endrep_a=endrep_a+1
				end
				if(if_a==endif_a and re==endrep_a)
				then
				break
			end
				pa=pa+1
		end
		if(if_a~=endif_a)
		then
		errorcount=errorcount+1
		err[errorcount]=pa..'：endif个数与if的数量不匹配！<if：'..if_a..'|endif：'..endif_a..'>'
		elseif(re~=endrep_a)
		then
		errorcount=errorcount+1
		err[errorcount]=pa..'：endrep个数与rep的数量不匹配！<rep：'..re..'|endrep：'..endrep_a..'>'
	else
		local i=1
		main_sa=nil
		while(i<toa+1)
			do
			if(isin(main_stack[i][1],set_struct,6)==true)
				then
				if(main_stack[i][1]=='if')
					then
					if(calculate(main_stack[i][2])==false)
						then
						while(main_stack[i][1]~='endif')
							do
							i=i+1
						end
					end
				elseif(main_stack[i][1]=='rep')
					then
					if(calculate(main_stack[i][2])==false)
						then
						while(main_stack[i][1]~='endrep')
							do
							i=i+1
						end
					end
					elseif(main_stack[i][1]=='endrep')
					then
					while(main_stack[i][1]~='rep')
						do
						i=i-1
					end
					i=i-1
				end
			elseif(isin(main_stack[i][1],set_nonstruct,7)==true)
				then
				identfy_nonstruct(main_stack[i])
			else
				errorcount=errorcount+1
				err[errorcount]=(pa-toa+i)..'：错误：未知的指令<'..main_stack[i][1]..'>'
			end
			i=i+1
		end
		end
		end
		pa=pa+1
	end
	if(errorcount>0)
		then
	while(errorcount>0)
		do
		print(err[errorcount])
		errorcount=errorcount-1
	end
end
set_struct=nil
set_nonstruct=nil
zero=nil
err=nil
main_stack=nil
re_pos=nil
end_pos=nil
all_code=nil
yxj=nil
end
explainer(parseCode(all_code))
