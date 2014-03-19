(* 2006-04-28 23:06:30 *)
program pku1038;
  var
    d,n,m:byte;
    tot:integer;
    s,t:byte;
    pow:array[0..10] of word;
    bad:array[1..150,1..10] of boolean;
    num:array[1..10] of byte;
    q:array[1..10,1..2] of boolean;
    f:array[1..2,0..59048] of byte;

procedure precalc;
  var i:byte;
  begin
    pow[0]:=1;
    for i:=1 to 10 do pow[i]:=pow[i-1]*3
  end;

procedure init;
  var i:integer;
      x,y:byte;
  begin
    readln(n,m,tot);
    fillchar(bad,sizeof(bad),false);
    for i:=1 to tot do begin
      readln(x,y);
      bad[x,m-y+1]:=true
    end
  end;

procedure main;
  var i:byte;
      j,k,l,max,value:word;

  procedure search(p,add:byte);
    begin
      if p=m+1 then begin
        value:=0;
        for p:=m downto 1 do
         if q[p,2] then value:=value*3+2
          else if q[p,1] then value:=value*3+1
                         else value:=value*3;
        if (f[t,value]=255)or(f[s,j]+add>f[t,value]) then
         f[t,value]:=f[s,j]+add
      end
      else begin
        if (p<m)and(not q[p,2])and(not q[p+1,2])and(num[p]=0)and(num[p+1]=0)
         then begin
           q[p,1]:=true;q[p,2]:=true;
           q[p+1,1]:=true;q[p+1,2]:=true;
           search(p+2,add+1);
           q[p,1]:=false;q[p,2]:=false;
           q[p+1,1]:=false;q[p+1,2]:=false;
         end;
        if (p+1<m)and(not (q[p,1] or q[p,2] or q[p+1,1] or q[p+1,2] or q[p+2,1] or q[p+2,2]))
         then begin
           q[p,1]:=true;q[p,2]:=true;
           q[p+1,1]:=true;q[p+1,2]:=true;
           q[p+2,1]:=true;q[p+2,2]:=true;
           search(p+3,add+1);
           q[p,1]:=false;q[p,2]:=false;
           q[p+1,1]:=false;q[p+1,2]:=false;
           q[p+2,1]:=false;q[p+2,2]:=false
         end;
        search(p+1,add)
      end
    end;

  begin
    fillchar(f[1],sizeof(f[1]),255);
    f[1,pow[m]-1]:=0;
    s:=2;t:=1;
    for i:=0 to n-1 do begin
      s:=3-s;t:=3-t;
      fillchar(f[t],sizeof(f[t]),255);
      for j:=0 to pow[m]-1 do if f[s,j]<255 then begin
        k:=j;
        fillchar(q,sizeof(q),false);
        for l:=1 to m do begin
          num[l]:=k mod 3;
          k:=k div 3;
          if num[l]=2 then q[l,1]:=true;
          if bad[i+1,l] then q[l,2]:=true
        end;
        search(1,0)
      end
    end;
    max:=0;
    for j:=0 to pow[m]-1 do
     if (f[t,j]<255)and(f[t,j]>max) then max:=f[t,j];
    writeln(max)
  end;

begin
  precalc;
  readln(d);
  for d:=1 to d do begin
    init;
    main
  end
end.
