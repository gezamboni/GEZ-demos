import boto3

# Get the device resource
sqs = boto3.resource('sqs')

# Podemos agora listar as queues
for queue in sqs.queues.all():
    print(queue.url)
