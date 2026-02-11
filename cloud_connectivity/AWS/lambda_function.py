import json

def lambda_handler(event, context):
    method = event["requestContext"]["http"]["method"]

    if method == "POST":
        body = json.loads(event["body"])
        print("DEVICE DATA:", body)
        return {
            "statusCode": 200,
            "headers": {"Content-Type": "application/json"},
            "body": json.dumps({
                "message": "Data received",
                "data": body
            })
        }

    elif method == "GET":
        return {
            "statusCode": 200,
            "headers": {"Content-Type": "application/json"},
            "body": json.dumps({
                "message": "message from post"
            })
        }
