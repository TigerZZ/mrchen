package com.haiersoft.ch05.test;

import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.hibernate.cfg.Configuration;

import com.haiersoft.ch05.pojos.Customer;

public class CustomerTest {

	public static void main(String[] args) {
			Customer c = new Customer("zhangsan", "123456","ÕÅÈý", "Çàµº", "13656687979");
			Configuration configuration = new Configuration();
			configuration.configure("/hibernate.cfg.xml");
			SessionFactory factory = configuration.buildSessionFactory();
			org.hibernate.Session session = factory.openSession();
			Transaction trans	 = session.beginTransaction();
			session.save(c);
			trans.commit();
			session.close();
	}

}
