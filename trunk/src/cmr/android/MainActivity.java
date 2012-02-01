package cmr.android;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ListView;
import android.widget.TextView;

public class MainActivity extends Activity {
    /** Called when the activity is first created. */
	public static final int Tag[] = {R.string.use_handler, R.string.get_systemRes, R.string.screenprotect};
	
	
	ListView mListView;
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        mListView = (ListView)findViewById(R.id.listView1);
        mListView.setAdapter(new MyAdapter(this, Tag));
        mListView.setOnItemClickListener(new ListViewOnItemClickListener());
        
    }
    
    
    private class ListViewOnItemClickListener implements OnItemClickListener{

		@Override
		public void onItemClick(AdapterView<?> arg0, View arg1, int arg2,
				long arg3) {
			// TODO Auto-generated method stub
			if(arg2 ==0)
			{
			Intent intent = new Intent();
			intent.setClass(MainActivity.this, HandlerActivity.class);
			startActivity(intent);
			}
			if(arg2 == 1)
			{
				Intent intent = new Intent();
				intent.setClass(MainActivity.this,ProgressBarActivity.class);
				startActivity(intent);
			}
			if(arg2 == 2)
			{
				Intent intent = new Intent();
				intent.setClass(MainActivity.this, ScreenProtect.class);
				startActivity(intent);
			}
			
		}
    	
    }
    
}