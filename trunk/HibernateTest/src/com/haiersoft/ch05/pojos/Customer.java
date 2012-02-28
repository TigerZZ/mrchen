package com.haiersoft.ch05.pojos;

import java.io.PrintWriter;
import java.io.Serializable;

public class Customer implements Serializable {
	private Integer id;
	private String userName;
	private String  passWord;
	private String  realName;
	private String address;
	private String mobile;
	public Integer getId() {
		return id;
	}
	public void setId(Integer id) {
		this.id = id;
	}
	public String getUserName() {
		return userName;
	}
	public void setUserName(String userName) {
		this.userName = userName;
	}
	public String getPassWord() {
		return passWord;
	}
	public void setPassWord(String passWord) {
		this.passWord = passWord;
	}
	public String getRealName() {
		return realName;
	}
	public void setRealName(String realName) {
		this.realName = realName;
	}
	public String getAddress() {
		return address;
	}
	public void setAddress(String address) {
		this.address = address;
	}
	public String getMobile() {
		return mobile;
	}
	public void setMobile(String mobile) {
		this.mobile = mobile;
	}
	
	public Customer(String userName, String passWord,
			String realName, String address, String mobile) {
		this.userName = userName;
		this.passWord = passWord;
		this.realName = realName;
		this.address = address;
		this.mobile = mobile;
	}
	
}
