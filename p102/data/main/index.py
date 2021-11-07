import json
import time
import traceback
import io
import sys
import numpy as np

ret = {
    'code': 0,
    'msg': 'ok',
    'data': []
}

class NpEncoder(json.JSONEncoder):
    def default(self, obj):
        if isinstance(obj, np.integer):
            return int(obj)
        elif isinstance(obj, np.floating):
            return float(obj)
        elif isinstance(obj, np.ndarray):
            return obj.tolist()
        else:
            return super(NpEncoder, self).default(obj)


stdout = sys.stdout
stderr = sys.stderr
_stdout = sys.__stdout__
_stderr = sys.__stderr__
f = io.StringIO()
sys.stdout = f
sys.stderr = f
sys.__stdout__ = f
sys.__stderr__ = f

try:
    from solution import Solution

    sln = Solution()
    result = sln.compute()
    ret['data'] = result
except Exception as e:
    ret['code'] = -1
    ret['msg'] = traceback.format_exc()

sys.stdout = stdout
sys.stderr = stderr
sys.__stdout__ = _stdout
sys.__stderr__ = _stderr
msg = f.getvalue()
if len(msg) > 0:
    ret['msg'] = msg

try:
    print(json.dumps(ret, cls=NpEncoder), end='')
except Exception as e:
    ret['code'] = -2
    ret['msg'] = traceback.format_exc()
    ret['data'] = {}
    print(json.dumps(ret), end='')