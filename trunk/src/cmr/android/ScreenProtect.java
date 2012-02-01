package cmr.android;



import java.util.Date;

import android.app.Activity;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.LayoutInflater;
import android.view.Window;
import android.view.WindowManager;
import android.widget.ImageView;

public class ScreenProtect extends Activity {
	/*****
	 * 
	 */
	ImageView mImageView;
	Date lastUpdateTime;//上一次更新时间
	long timeStatic  = 0;
	int intDrawable = 0;
	
	private static final  int screenDrawable[] = {
		R.drawable.a,
		R.drawable.b,
		R.drawable.c,
		R.drawable.d,
		R.drawable.e
	}; 
	




	@Override
	protected void onStop() {
		// TODO Auto-generated method stub
		handler1.removeCallbacks(mTask1)
		;
		super.onDestroy();
	}

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		//全屏模式
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		getWindow().setFlags
		(
			WindowManager.LayoutParams.FLAG_FULLSCREEN,
			WindowManager.LayoutParams.FLAG_FULLSCREEN
		);
		setContentView(R.layout.screenprotect);
		
		lastUpdateTime = new Date(System.currentTimeMillis());
		mImageView = (ImageView)findViewById(R.id.screemimage);	
		handler1.post(mTask1)
		;
	}
	
	Handler handler1 = new Handler(){
		public void handleMessage(Message msg) {
			System.out.println("处理消息");
			handler1.post(mTask1);
			
		}
	};
	/**
	 * 监控User没有动作的线程
	 */
	private Runnable mTask1 = new Runnable() {
		@Override
		public void run() {
			Date timeNow = new Date(System.currentTimeMillis());
			timeStatic = timeNow.getTime() - lastUpdateTime.getTime(); 
			System.out.println(timeStatic);
			if(timeStatic % 2500 == 0)
			{
				lastUpdateTime.setTime(System.currentTimeMillis());
				intDrawable++;
				showScreenSaver();
			}
			handler1.post(mTask1);
		}
	};
	
	private void showScreenSaver()
	{
		if (intDrawable  > 4) 
		{
			intDrawable = 0;
		}
		mImageView.setImageBitmap(BitmapFactory.decodeResource(
				getResources(), screenDrawable[intDrawable]));
	
	}
}
