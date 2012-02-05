package cmr.test;
import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;


public class MySAX extends DefaultHandler {

	public void characters(char[] arg0, int arg1, int arg2) throws SAXException {
		// TODO Auto-generated method stub
		System.out.print(new String(arg0,arg1,arg2));
	}


	public void endDocument() throws SAXException {
		// TODO Auto-generated method stub
		System.out.println("ÎÄµµ½âÎö½áÊø");
	}

	public void endElement(String arg0, String arg1, String arg2)
			throws SAXException 
		// TODO Auto-generated method stub
	    {
		System.out.print("<");
			System.out.print(arg2);
			System.out.print(">");
	     }
	

	public void startDocument() throws SAXException {
		// TODO Auto-generated method stub
		System.out.println("<?xml version=\"1.0\" encoding=\"GBK\"?>");
	}

	public void startElement(String uri, String localName, String qName, Attributes attributes) throws SAXException
    {
		System.out.print("<");
		System.out.print(qName);
		
		if (attributes !=null) {
			for (int i = 0; i < attributes.getLength(); i++) {
				System.out.print(" "+attributes.getQName(i)+"="+"\"" +attributes.getValue(i)+"\"");
			}
		}
		System.out.print(">");
    }

}
