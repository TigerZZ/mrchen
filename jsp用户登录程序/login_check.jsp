<%@page contentType="text/html; charset=GBK"  %>
<%@page import="java.sql.*" %>

<html>
	<head><title>简单登陆程序模块</title></head>
<body>
	<center>
	<h1>登陆操作</h1>
		<hr>
	<%! //定义一些常量
		public static final String DBDRIVER = "org.gjt.mm.mysql.Driver";
		public static final String DBUSER = "root";
		public static final String DBURL = "jdbc:mysql://localhost:3306/mldn";
		public static final  String DBPASS= "mysqladmin";
	%>
	<%
		Connection conn = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;
		boolean flag =false;
		String name=null;
	%>
	<%
	try{
	%>
	<%
		Class.forName(DBDRIVER);
		conn = DriverManager.getConnection(DBURL,DBUSER,DBPASS);
		String sql = "SELECT  name FROM USER WHERE userid=? and password=?";
		pstmt = conn.prepareStatement(sql);
		pstmt.setString(1,request.getParameter("id"));
		pstmt.setString(2,request.getParameter("password"));
		rs = pstmt.executeQuery();
		if(rs.next())
		{
			flag = true;
			name=rs.getString(1);
		}
 	%>
 	<%
 	}catch(Exception e){
 		e.printStackTrace();
 	}
 	finally{
 	try{
 		pstmt.close();
		conn.close();
		rs.close();
 	}
 	catch(Exception e){}
 	}
 	%>
 	<%
 		if(flag)
 		{
 		
 	%>

 	<%
 		
 	
 	%>
 		<jsp:forward page="login_success.jsp">
 			<jsp:param name="uname" value="<%=name%>"/>
 		</jsp:forward>
 	<%	
 		}
 	else{
 			System.out.print("------------------");
 	%>
	 	<jsp:forward page="login_failure.jsp"/>
	 
 	<%
 		}
 	%>
</center>
</body>
</html>