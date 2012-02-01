package cmr.android;

import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLConnection;

import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.provider.ContactsContract.CommonDataKinds.Im;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.Toast;

public class HandlerActivity extends Activity {
	ImageView mImageView;
	Button mButton;
	static final String IMG_URL="http://www.qqwen.cc/uploads/allimg/c090923/1253E3VI3330-12L227.jpg"; 

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.handler);
		mButton = (Button)findViewById(R.id.button1);
		mButton.setOnClickListener(new ButtonOnClickListener());
		mImageView = (ImageView)findViewById(R.id.imageView1);
		
		
		findViewById(R.id.loadimgbutton).setOnClickListener(new View.OnClickListener() {
			public void onClick(View arg0) {
				new Thread(new Runnable() {
					
					@Override
					public void run() {
						try{
							URL url = new URL(IMG_URL);
							HttpURLConnection httpURLConnection= (HttpURLConnection)url.openConnection();
							httpURLConnection.connect();
							final Bitmap bm = BitmapFactory.decodeStream(httpURLConnection.getInputStream());
							
							mImageView.post(new Runnable() {
								
								@Override
								public void run() {
									// TODO Auto-generated method stub
									mImageView.setImageBitmap(bm);
								}
							});
							
						}
					catch (Exception e) {
						e.printStackTrace();
					}
				}}).start();
			}
		});
	}

	private void setImage(String urlString) {
		try {
			
			URL url = new URL(urlString);
			HttpURLConnection httpURLConnection= (HttpURLConnection)url.openConnection();
			httpURLConnection.connect();
			Bitmap bm = BitmapFactory.decodeStream(httpURLConnection.getInputStream());
			if(bm == null)
				System.out.println("No Image");
			
			mImageView = (ImageView)findViewById(R.id.imageView1);
			 mImageView.setImageBitmap(bm);
		} catch (Exception e) {
			// TODO: handle exception
			e.printStackTrace();
		}
	}
	
	class  ButtonOnClickListener implements OnClickListener{
		@Override
		public void onClick(View v) {
				setImage(IMG_URL);
		}
	}
	
}
